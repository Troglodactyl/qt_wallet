#pragma once

#include <QObject>
#include <QVariant>

#include <bts/rpc/rpc_server.hpp>
#include <bts/client/client.hpp>

class ClientWrapper : public QObject 
{
    Q_OBJECT

  public:
    ClientWrapper(QObject *parent = nullptr);
    ~ClientWrapper();

    ///Not done in constructor to allow caller to connect to error()
    void initialize();

    QUrl http_url() const;

    Q_INVOKABLE QVariant get_info();
    Q_INVOKABLE QString get_http_auth_token();
    std::shared_ptr<bts::client::client> get_client() { return _client; }

  public Q_SLOTS:
    void confirm_and_set_approval(QString delegate_name, bool approve);
    void close();

  Q_SIGNALS:
    void initialized();
    void status_update(QString statusString);
    void error(QString errorString);

  private:
    bts::client::config                  _cfg;
    std::shared_ptr<bts::client::client> _client;
    fc::thread                           _bitshares_thread;
    fc::future<void>                     _init_complete;
    fc::optional<fc::ip::endpoint>       _actual_httpd_endpoint;
};
