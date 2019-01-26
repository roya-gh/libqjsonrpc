#include "jsonrpcresponse.h"


JsonRPCResponse::JsonRPCResponse(int id, const QString& jsonrpcV)
    : m_id(id), m_jsonrpcV(jsonrpcV) {

}

const QString& JsonRPCResponse::jsonrpcV() {
    return m_jsonrpcV;
}



int JsonRPCResponse::id() {
    return m_id;
}


void JsonRPCResponse::setJsonrpcV(const QString& jsonrpcv) {
    m_jsonrpcV = jsonrpcv;
}



void JsonRPCResponse::setId(int id) {
    m_id = id;
}

