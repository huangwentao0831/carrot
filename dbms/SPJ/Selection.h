#ifndef  SELECTION_H_INCLUDED
#define SELECTION_H_INCLUDED
#include"SPJ.h"
#include"../util/DataUtil.h"
#include <string>
#include<map>
typedef struct {
    Byte conditionType;//value or column
    string filedName;
    void*value;
    Byte  compare;
    Byte DataType;
    int len;
}Condition;

class CompareType{
public:
static const Byte LESS=2;
static const Byte  GREATER=3;
static const Byte   EQUAL=0;
static const Byte  GREATEREQUAL=4;
static const Byte  LESSEQUAL=5;
static const Byte  NOTEQUAL=1;
public :
      static bool Compare(void*value1,void*value2,Byte cmpType,int dataType,int len){
            Byte*data1=new Byte[len];
            Byte*data2=new Byte[len];
            memcpy(data1,value1,len);
            memcpy(data2,value2,len);
            int result=DataUtil::cmpData(data1,data2,dataType,len);
          switch(cmpType){
            case CompareType::LESS:
                if(result<0){
                    return true;
                }else{
                    return false;
                }
            case CompareType::GREATER:
                if(result>0){
                    return true;
                }else{
                    return false;
                }
                case CompareType::GREATEREQUAL:
                if(result>0||result==0){
                    return true;
                }else{
                    return false;
                }
                case CompareType::LESSEQUAL:
                if(result<0||result==0){
                    return true;
                }else{
                    return false;
                }
                case CompareType::EQUAL:
                if(result==0){
                    return true;
                }else{
                    return false;
                }
                case CompareType::NOTEQUAL:
                if(result!=0){
                    return true;
                }else{
                    return false;
                }
          }
    }

    static int compare(void*value1,void*value2,int len){
            Byte*data1=new Byte[len];
            Byte*data2=new Byte[len];
            memcpy(data1,value1,len);
            memcpy(data2,value2,len);
                int flag=1;
                for(int i=0;i<len;i++){
                    if(data1[i]<data2[i]){
                        flag=0;
                        break;
                    }else if(data1[i]>data2[i]){
                        flag=2;
                        break;
                    }
                }
                return flag;
    }
};

class Selection :public SPJ{
public:
    void getNext(SPJItem*item);
    void getFirst(SPJItem * item);
    void initSelection(Table*table,Condition*condition,int conditionLen);
    void initSelection(SPJ*spj,Condition*condition,int conditionLen);
    void releaseSPJItem(SPJItem*item);
    IndexIterator* checkIndex();
    bool checkItem(Tuple *tuple);
    bool checkItem(SPJItem*sourceItem);
    SPJItem* buildSPJItem();
    Selection(int type,int initial);
    void fillItem(SPJItem*item,Tuple *tuple);
    void fillItem(SPJItem*item,SPJItem* sourceItem);
     IndexIterator*getIndexIterator(IndexMetaItem item,vector<Condition>conditionlist,IndexSegment*indexSegment);
     void destroy();
private:
        Byte initialType;//
        Tuple*currentTuple;//now the tuple
        Byte operatorType;
        string*columns;
        int columnNum;
         Condition*condition;
        int conditionLen;
        Byte*dataType;
        SPJ*spj;
        Index*index;
        IndexIterator*indexIterator;
};
#endif // SELECTION_H_INCLUDED