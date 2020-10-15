#include "publisherzmq.h"

PublisherZMQ::PublisherZMQ(QObject *parent) : QObject(parent)
{

}

zmq::context_t *PublisherZMQ::context() const
{
    return mContext;
}

void PublisherZMQ::setContext(zmq::context_t *context)
{
    mContext = context;
}

zmq::socket_t *PublisherZMQ::socket() const
{
    return mSocket;
}

void PublisherZMQ::setSocket(zmq::socket_t *socket)
{
    mSocket = socket;
}

void PublisherZMQ::start()
{
    int num = 0;

    while(true)
    {
        zmq::message_t msg;
        msg.rebuild(sizeof (int));
        memcpy(msg.data(), &(++num), sizeof (int));
        mSocket->send(msg);

        qInfo() << "Message Sent...";
        QThread::currentThread()->msleep(1000);
    }

}
