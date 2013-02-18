//
//  MongoConn.hpp
//  MongoConn
//
//  Created by Chengfu on 13-2-18.
//  Copyright (c) 2013年 PongStudio. All rights reserved.
//

#ifndef MongoConn_MongoConn_hpp
#define MongoConn_MongoConn_hpp


#include <iostream>
#include "mongo/client/dbclient.h"
using namespace mongo;
#include <string>
using namespace std;
bool SaveFile(string dbNm,string fileNm){
    
    DBClientBase *conn = NULL;
    string err_msg;
    ConnectionString cs = ConnectionString::parse("localhost", err_msg);
    
    GridFS * fs;
    
    
    
    
    if (!cs.isValid()) {
        throw "bad: " + err_msg;
    }
    
    try {
        conn = cs.connect(err_msg);
        fs = new GridFS(*conn,dbNm);
        BSONObj p = fs->storeFile(fileNm);
        conn->insert("db.coll",p,0);
    } catch (DBException &e) {
        cout << "caught " << err_msg << endl;
        return false;
    }
    
    if (!conn){
        cout<<"Unable to connect to DB"<<endl;
        return false;
    }
    
    return true;
};

#endif
