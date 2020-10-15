#ifndef PUBLISHERZMQ_H
#define PUBLISHERZMQ_H

#include <QObject>
#include <zmq.hpp>
#include <QThread>
#include <QDebug>

class PublisherZMQ : public QObject
{
    Q_OBJECT
public:
    explicit PublisherZMQ(QObject *parent = nullptr);

    zmq::context_t *context() const;
    void setContext(zmq::context_t *context);

    zmq::socket_t *socket() const;
    void setSocket(zmq::socket_t *socket);

signals:


public slots:
    void start();

private:
    zmq::context_t* mContext;
    zmq::socket_t*  mSocket;

};

#endif // PUBLISHERZMQ_H
