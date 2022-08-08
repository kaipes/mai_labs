#include <unordered_map>
#include <unistd.h>
#include <sstream>
#include <zmq.hpp>
#include <iostream>

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

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        throw runtime_error("Wrong args for counting node");
    }
    int cur_id = atoi(argv[1]);
    int child_id = -1;
    if (argc == 3) {
        child_id = atoi(argv[2]);
    }

    unordered_map<string, int> dictionary;

    zmq::context_t context;
    zmq::socket_t parent_socket(context, ZMQ_REP);
    
    string adr = "tcp://127.0.0.1:" + to_string(MAIN_PORT + cur_id);
    parent_socket.connect(adr);

    zmq::socket_t child_socket(context, ZMQ_REQ);
    if (child_id != -1) {
        adr = "tcp://127.0.0.1:" + to_string(MAIN_PORT + child_id);
        child_socket.bind(adr);
    }
    child_socket.setsockopt(ZMQ_SNDTIMEO, 5000);
 
    string message;
    while (true) {
        message = receive_message(parent_socket);
        istringstream request(message);
        int dest_id;
        request >> dest_id;

        string command;
        request >> command;

        if (dest_id == cur_id) {
    
            if (command == "pid") {

                send_message(parent_socket, "OK: " + to_string(getpid()));

            } else if (command == "create") {

                int new_child_id;
                request >> new_child_id;
                if (child_id != -1) {
                    adr = "tcp://127.0.0.1:" + to_string(MAIN_PORT + child_id);
                    child_socket.unbind(adr);
                }

                adr = "tcp://127.0.0.1:" + std::to_string(MAIN_PORT + new_child_id);
                child_socket.bind(adr);
                pid_t pid = fork();
                if (pid < 0) {
                    cout << "Can't create new process" << endl;
                    return -1;
                }
                if (pid == 0) {
                    execl("./counting", "./counting", to_string(new_child_id).c_str(), to_string(child_id).c_str(), NULL);
                    cout << "Can't execute new process" << endl;
                    return -2;
                }
                send_message(child_socket, to_string(new_child_id) + " pid");
                child_id = new_child_id;
                send_message(parent_socket, receive_message(child_socket));

            } else if (command == "check") {
                string key;
                request >> key;
                if (dictionary.find(key) != dictionary.end()) {
                    send_message(parent_socket, "OK: " + std::to_string(cur_id) + ": " + std::to_string(dictionary[key]));
                } else {
                    send_message(parent_socket, "OK: " + std::to_string(cur_id) + ": '" + key + "' not found");
                }
            } else if (command == "add") {
                string key;
                int value;
                request >> key >> value;
                dictionary[key] = value;
                send_message(parent_socket, "OK: " + to_string(cur_id));
            }   else if (command == "pingall") {
                string reply;
                if (child_id != -1) {
                    send_message(child_socket, to_string(child_id) + " pingall");
                    string msg = receive_message(child_socket);
                    reply += " " + msg;
                }
                send_message(parent_socket, to_string(cur_id) + reply);
            } else if (command == "kill") {
                if (child_id != -1) {
                    send_message(child_socket, std::to_string(child_id) + " kill");
                    std::string msg = receive_message(child_socket);
                    if (msg == "OK") {
                        send_message(parent_socket, "OK");
                    }
                    string adr = "tcp://127.0.0.1:" + std::to_string(MAIN_PORT + child_id);
                    child_socket.unbind(adr);
                    std::string address = "tcp://127.0.0.1:" + std::to_string(MAIN_PORT + cur_id);
                    parent_socket.disconnect(address);
                    //disconnect(parent_socket, cur_id);
                    break;
                }
                send_message(parent_socket, "OK");
               // disconnect(parent_socket, cur_id);
                 std::string address = "tcp://127.0.0.1:" + std::to_string(MAIN_PORT + cur_id);
                    parent_socket.disconnect(address);
                break;
            }
        }      
         else if (child_id != -1) {
            send_message(child_socket, message);
            send_message(parent_socket, receive_message(child_socket));
            if (child_id == dest_id && command == "kill") {
                child_id = -1;
            }
        } else {
            send_message(parent_socket, "Error: node is unavailable");
        }
    }
}