#include "api/DBusClient.h"
#include <iostream>
#include <string.h>


DBusClient::DBusClient() : dispatcherPtr(new DBus::DefaultDispatcher()), conn(dispatcherPtr) {
    try {
        // Initialize the connection with the dispatcher
        conn->enter();  // Dereference the pointer before calling the method
    } catch (DBus::Error& e) {
        std::cerr << "Failed to create D-Bus connection: " << e.what() << std::endl;
        delete dispatcherPtr;
        throw;  // Re-throw the exception for the caller to handle if needed
    }
}

DBusClient::~DBusClient() {
    // Clean up resources
    delete dispatcherPtr;
}

bool DBusClient::connectToDBus() {
    // No need to enter again, as it's already done in the constructor
    return true;
}

// Rest of your implementation remains the same...



std::string DBusClient::createData(const std::string& data) {
    return invokeMethod("Create", 0, data);
}

std::string DBusClient::readData(int id) {
    return invokeMethod("Read", id, "");
}

bool DBusClient::updateData(int id, const std::string& newData) {
    invokeMethod("Update", id, newData);
    return true; // You may include error handling logic here
}

bool DBusClient::deleteData(int id) {
    invokeMethod("Delete", id, "");
    return true; // You may include error handling logic here
}

std::string DBusClient::invokeMethod(const char* methodName, int id, const std::string& data) {
    try {
        DBus::Message msg = conn->call_method("com.example.DatabaseManager", "/" /* object path */, "com.example.DatabaseManager", methodName, id, data);
        std::string result;
        msg >> result;
        return result;
    } catch (DBus::Error& e) {
        std::cerr << "D-Bus method invocation error: " << e.what() << std::endl;
        return ""; // You may handle errors more appropriately
    }
}
