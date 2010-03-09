#include "httpclient.h"

/**
  *@brief Constructor, connects object to GUI
  *@param Pointer to carmainwindow, which is temporarily used during development
  */
HttpClient::HttpClient()
{
    netManager = new QNetworkAccessManager();
}

/**
  *@brief Destructor
  */
HttpClient::~HttpClient()
{

}
