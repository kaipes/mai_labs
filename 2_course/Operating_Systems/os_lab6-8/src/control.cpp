#include <unistd.h>
#include <sstream>
#include <set>
#include <zmq.hpp>
#include <iostream>
#include "list_of_list.h"
using namespace std;
const int MAIN_PORT = 4040;

void send_message(zmq::socket_t& socket, const string& msg) {

    zmq::message_t message(msg.size());
    memcpy(message.data(), msg.c_str(), msg.size());
    socket.send(message);

}

string receive_message(zmq::socket_t& socket) {

    zmq::message_t message;
    int chars_read;
    try {
        chars_read = (int)socket.recv(&message);
    }
    catch (...) {
        chars_read = 0;
    }
    if (chars_read == 0) {
        return "Error: node is unavailable [zmq_func]";
    }
    string received_msg(static_cast<char*>(message.data()), message.size());
    return received_msg;

}
 
int main() {
    
    list_of_list network;
    std::vector<zmq::socket_t> branches;
    zmq::context_t context;

    string command;

    while (true) {
        cin >> command;
        if (command == "create") {
            int node_id, parent_id;
            cin >> node_id >> parent_id;
            if (network.find(node_id) != -1) {
                cout << "Error: Already exists" << endl;
            } else if (parent_id == -1) {
                pid_t pid = fork();
                if (pid < 0) {
                    cout << "Can't create new process" << endl;
                    return -1;
                } else if (pid == 0) {
                    execl("./counting", "./counting", to_string(node_id).c_str(), NULL);
                    cout << "Can't execute new process" << endl;
                    return -2;
                }
                branches.emplace_back(context, ZMQ_REQ);
                branches[branches.size() - 1].setsockopt(ZMQ_SNDTIMEO, 5000);
                string adr = "tcp://127.0.0.1:" + to_string(MAIN_PORT + node_id);
                branches[branches.size()-1].bind(adr);
            
                send_message(branches[branches.size() - 1], to_string(node_id) + " pid");
                
                string reply = receive_message(branches[branches.size() - 1]);
                cout << reply << endl;
                network.insert(node_id, parent_id);

            } else if (network.find(parent_id) == -1) {

                cout << "Error: Parent not found" << endl;

            } else {
                int branch = network.find(parent_id);
                send_message(branches[branch], to_string(parent_id) + "create " + to_string(node_id));

                string reply = receive_message(branches[branch]);
                cout << reply << endl;
                network.insert(node_id, parent_id);
            }
        } else if (command == "exec") {
            string s;
            getline(cin, s);
            string exec_command;
            vector<string> tmp;
            string tmp1 = "";
            for (int i = 1; i < s.size();i++) {
                tmp1+=s[i];
                if (s[i] ==' ' || i == s.size()-1) {
                    tmp.push_back(tmp1);
                    tmp1 = "";
                }
            }
            if (tmp.size() == 2) {
                exec_command = "check";
            } else {
                exec_command = "add";
            }
            int dest_id = stoi(tmp[0]);
            int branch = network.find(dest_id);
            if (branch == -1) {
                cout << "There is no such node id" << endl;
            } else {
                if (exec_command == "check") {
                    send_message(branches[branch], tmp[0]+" check "+tmp[1]);
                
                } else if (exec_command == "add") {
                    string value;
                    send_message(branches[branch], tmp[0]+" add "+tmp[1]+" "+tmp[2]);
                }
                string reply = receive_message(branches[branch]);
                cout << reply << endl;
            }
        } else if (command == "kill") {
            int id;
            cin >> id;
            int branch = network.find(id);
            if (branch == -1) {
                cout << " Error: incorrect node id" << endl;
            } else {
                bool is_first = (network.get_first_id(branch) == id);
                send_message(branches[branch], to_string(id)+"kill");
                 std::string reply = receive_message(branches[branch]);
                std::cout << reply << std::endl;
                network.erase(id);
                if (is_first) {
                    string address = "tcp://127.0.0.1:" + std::to_string(MAIN_PORT + id);
                    branches[branch].unbind(address);
                    branches.erase(branches.begin() + branch);
                }
            }
        } else if (command == "pingall") {
            set<int> available_nodes;
            for (size_t i = 0; i < branches.size(); ++i) {
                int first_node_id = network.get_first_id(i);
                send_message(branches[i], std::to_string(first_node_id) + " pingall");

                string received_message = receive_message(branches[i]);
                istringstream reply(received_message);
                int node;
                while(reply >> node) {
                    available_nodes.insert(node);
                }
            }
            cout << "OK: ";
            if (available_nodes.empty()) {
                cout << "no available nodes" << endl;
            }
            else {
                for (auto v : available_nodes) {
                    cout << v << " ";
                }
                cout << endl;
            }
        } else if (command == "exit") {
            for (size_t i = 0; i < branches.size(); ++i) {
                int first_node_id = network.get_first_id(i);
                send_message(branches[i], to_string(first_node_id) + " kill");
                string reply = receive_message(branches[i]);
                if (reply != "OK") {
                    cout << reply << endl;
                } else {
                    string adr = "tcp://127.0.0.1:" + to_string(MAIN_PORT + first_node_id);
                    branches[i].unbind(adr);
                }
            }
            exit(0);
        } else {
            cout << "Not correct command" << endl;
        }
    }
}