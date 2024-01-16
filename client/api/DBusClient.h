#ifndef DBUS_CLIENT_H
#define DBUS_CLIENT_H

#include <iostream>
#include <string>
#include <dbus-c++-1/dbus-c++/dbus.h>

class DBusClient {
public:
    DBusClient(); // default constructor
    ~DBusClient(); // destructor

    bool connectToDBus();
    std::string createData(const std::string& data);
    std::string readData(int id);
    bool updateData(int id, const std::string& newData);
    bool deleteData(int id);

    //Getter and setter functions
    DBus::BusDispatcher getDispatcher() const { return dispatcher; }
    void setDispatcher(const DBus::BusDispatcher &dispatcher_) { dispatcher = dispatcher_; }

    DBus::Dispatcher* getDispatcherPtr() const { return dispatcherPtr; }
    void setDispatcherPtr(DBus::Dispatcher* dispatcherPtr_) { dispatcherPtr = dispatcherPtr_; }

    DBus::Connection* getConn() const { return conn; }
    void setConn(DBus::Connection* conn_) { conn = conn_; }

private:
    DBus::BusDispatcher dispatcher;
    DBus::Dispatcher* dispatcherPtr; // Using a pointer to the Dispatcher

    DBus::Connection* conn; // Using a pointer to the Connection

    std::string invokeMethod(const char* methodName, int id, const std::string& data);
};

#endif // DBUS_CLIENT_H
