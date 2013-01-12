//
//  main.cpp
//  TestMongo
//
//  Created by Chengfu on 13-1-12.
//  Copyright (c) 2013年 PongStudio. All rights reserved.
//

#include <iostream>
#include "mongo/client/dbclient.h"
using namespace mongo;
using namespace std;
int main(int argc, const char * argv[])
{
    DBClientBase *conn = NULL;
    string err_msg;
    ConnectionString cs = ConnectionString::parse("localhost", err_msg);
    
    if (!cs.isValid()) {
        throw "bad: " + err_msg;
    }
    
    try {
        conn = cs.connect(err_msg);
    } catch (DBException &e) {
        cout << "caught " << err_msg << endl;
        return 0;
    }
    
    if (!conn){
        cout<<"Unable to connect to DB"<<endl;
        return 0;
    }
    
    //        BSONObjBuilder b;
    //        b.append("name", "Joe");
    //        b.append("age", 33);
    //        BSONObj p = b.obj();
    //
    //        conn->insert("db.coll",p,0);
    
    
    GridFS * fs;
    
    fs = new GridFS(*conn,"test");
    BSONObj p = fs->storeFile("pic.JPG");
    conn->insert("db.coll",p,0);
    return 0;
}

