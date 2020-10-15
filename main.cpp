#include <QCoreApplication>
#include <zmq.hpp>
#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include "publisherzmq.h"

void subscriber(zmq::context_t* context)
{
    zmq::socket_t socket(*context, ZMQ_SUB);
    socket.connect("tcp://127.0.0.1:5000");
    QString filter = "";
    socket.setsockopt(ZMQ_SUBSCRIBE, filter.toStdString().c_str(), (int)filter.length());
    zmq::message_t msg;
    int num;

    while (true)
    {
        while(socket.recv(&msg, ZMQ_NOBLOCK))
        {
            memcpy(&num, msg.data(), msg.size());
            qInfo() << "Recived: " << num << " running on: " << QThread::currentThread();

        }

    }


}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    zmq::context_t context(1);
    zmq::socket_t  socket(context, ZMQ_PUB);
    socket.bind("tcp://*:5000");

    PublisherZMQ pub;

    pub.setContext(&context);
    pub.setSocket(&socket);

    QThread pubThread;
    QObject::connect(&pubThread, &QThread::started, &pub, &PublisherZMQ::start, Qt::QueuedConnection);
    pub.moveToThread(&pubThread);

    pubThread.start();

    QThreadPool   pool;
    QFuture<void> future1 = QtConcurrent::run(&pool, subscriber, &context);
    QFuture<void> future2 = QtConcurrent::run(&pool, subscriber, &context);
    QFuture<void> future3 = QtConcurrent::run(&pool, subscriber, &context);

    while(true)
    {
        subscriber(&context);
    }

    return a.exec();
}
