#include "iostream"
using namespace std;
#include "string.h"
#include "string"
#include "stdlib.h"
#include "stdio.h"
#include "resource.h"
#include "semantic.h"

#define deal(s) if(!(s)){return false;}
#define pdeal(s) if(!(s)){cout<<"没有找到文件结尾（程序是否未完成？）"<<endl;return false;}



//定义读入元素用的结构体及变量 
struct WORD{
    int type;
    int pos;
    bool normal;
    string att;
    string line;
    WORD(){normal=true;}
    bool readNext()
    {
        cin>>line;
        if(!cin){cin.clear();normal = false;return false;}
        while(line[0]!='(')
            cin>>line;
        att="";
        int i,j=0;
        int l = line.length();
        i=3;

        if(line[2]>='0'&&line[2]<='9')
        {
            type = (line[1]-'0')*10+(line[2]-'0');
            i=4;
        }
        else 
            type = line[1]-'0';

        for(;line[i]!=',';i++)
            att.push_back(line[i]);

        for(i=0;i<l;i++)
        {
            if(line[i]==',')j++;
            if(j==2)break;
        }
        i++;
        pos = 0;
        while(line[i]>='0'&&line[i]<='9')
        {
            pos = pos*10 + (line[i]-'0');
            i++;
        }
        return true;
    }
}word;


//定义函数 
bool error(string s);
bool P();
bool Sn(Sstruct &ss);
bool S(Sstruct &ss);
bool SDn();
bool SD();
bool SDT();
bool SA();
bool SIF(Sstruct &ss);
bool SELSE(Sstruct &ss);
bool SW(Sstruct &ss);
bool SC(Sstruct &ss);
bool B(Bstruct &bs);
bool BT(Bstruct &bs);
bool E(Estruct &es);
bool ET(Estruct &es);
bool A();
bool C();
bool D();


//函数实现 
bool error(string s)
{
    printf("语法错误：在第%d行\n",word.pos);
    cout<<s<<endl;
}

//P->program i;SDn SC;
bool P()
{


    pdeal(word.normal);
    bool ret = true;     
    Sstruct ss;

    if(word.type!= $program ){error("缺少程序定义语句");ret = false;}
    else pdeal(word.readNext());     

    if(word.type!=$flag){error("缺少程序名");ret = false;}
    else pdeal(word.readNext());          

    if(word.type!=$){error("缺少语句结束标志"); ret = false;}
    else pdeal(word.readNext());     

    if(!SDn())ret = false;     
    pdeal(word.normal);

    if(!SC(ss))ret = false;          
    pdeal(word.normal);  

    if(word.type!=$){error("缺少程序结束标志");    ret = false;}
    cout<<"程序"<<endl;      
    return ret;
}

//Sn->S;Sn|null
bool Sn(Sstruct &ss)
{

    deal(word.normal);   
    bool ret = true;
    while(word.type!=$if&&word.type!=$flag&&word.type!=$var&&word.type!=$while&&word.type!=$begin)
    {
        if(word.type==$end)
            return ret;
        error("语法错误"); 
        ret = false;
        deal(word.readNext());
    }

    if(!S(ss))ret = false;
    backpatch(ss.nextlist,quad);

    deal(word.normal);     
    if(word.type!=$){ret = false; error("缺少行终止符");}     
    else deal(word.readNext()); 
    if(!Sn(ss))ret = false;       
    deal(word.normal);   
    return ret;
}

//S->SD|SA|SIF|SW|SC
bool S(Sstruct &ss)
{
    deal(word.normal);   
    bool ret = true;
    switch(word.type)
    {
        case $if:return SIF(ss);
        case $var:
                 ss.nextlist=0;
                 return SD();
        case $flag: 
                 ss.nextlist=0;
                 return SA();
        case $while:return SW(ss);
        case $begin:return SC(ss);
        default: error("语法错误");
    }
}

//SDn->SD;SDn|null
bool SDn()
{

    deal(word.normal);

    if(word.type==$begin)
        return true;

    bool ret = true;
    while(true)
    {
        while(word.type!=$begin&&word.type!=$var)
        {
            error("语法错误");
            deal(word.readNext());
        } 
        if(word.type==$var)
        {
            if(!SD())
            {                            
                while(true)
                {   
                    if(word.type==$||word.type==$begin)break;
                    deal(word.readNext());
                }
            }
            else{
                if(word.type!=$)
                {
                    error("缺少行终止符");
                    ret = false;
                }else deal(word.readNext());
            }
        }
        if(word.type==$begin)break; 
    }

    return ret;
}

//SD->var int iSDT
bool SD()
{

    deal(word.normal);   
    bool ret = true;

    if(word.type!=$var)
    {
        error("语法错误");
        return false;
    }else word.readNext();
    deal(word.normal);   

    if(word.type!= $int )
    {
        error("语法错误");
        return false;
    }else word.readNext();
    deal(word.normal);   

    if(word.type!=$flag)
    {
        error("语法错误");
        return false;
    }else word.readNext(); 

    cout<<"定义语句"<<endl;  
    deal(word.normal);

    return SDT();     
}

//SDT -> null|,iSDT
bool SDT()
{
    deal(word.normal);   
    bool ret = true;
    if(word.type!=$comma)return true;

    word.readNext();
    deal(word.normal);   

    if(word.type!=$flag)
    {
        error("语法错误");
        return false;
    }else word.readNext();
    deal(word.normal);   

    return SDT();
}

//SA->i:=E
bool SA()
{  
    deal(word.normal);   
    string result;
    if(word.type!= $flag ){error("语法错误");return false;}
    else{
        result = word.att;
        deal(word.readNext()); 
    }
    deal(word.normal);   

    if(word.type!= $copy ){error("语法错误");return false;}

    cout<<"赋值语句"<<endl; 
    word.readNext();     
    deal(word.normal);   

    Estruct es;
    if(!E(es))return false;

    int quad = Nextquad();
    RSS[quad].setop(":=");
    RSS[quad].setpar1(es.lexval);
    RSS[quad].setresult(result);

    return true;
}

//SIF->if B then S SELSE
bool SIF(Sstruct &ss)
{

    deal(word.normal);   

    bool ret = true;     
    if(word.type!= $if )
    {
        ret =false;
        error("缺少if");
    }else word.readNext();

    deal(word.normal);  

    Bstruct bs;
    if(!B(bs))return false;

    if( word.type != $then )
    {
        ret = false;
        error("缺少then"); 
    }else word.readNext();   

    deal(word.normal);           
    cout<<"if-then语句嵌套"; 

    Mstruct m1;
    m1.quad = quad;

    Sstruct ss1;
    if(!S(ss1))return false;     
    deal(word.normal);    

    if(word.type!=$else)
    {
        ss.nextlist = merge(bs.falselist,ss1.nextlist);
        backpatch(bs.truelist,m1.quad);          
        return ret;
    }
    else
    {           
        Nstruct ns;
        ns.nextlist = Nextquad();
        RSS[ns.nextlist].setop("j");
        RSS[ns.nextlist].setjump(0);

        Mstruct m2;
        m2.quad = quad;

        Sstruct ss2;
        if(!SELSE(ss2))ret =false;
        deal(word.normal);    

        backpatch(bs.truelist,m1.quad);
        backpatch(bs.falselist,m2.quad);
        ss.nextlist = merge(merge(ss1.nextlist,ns.nextlist),ss2.nextlist);
        return ret;
    }
}

//SELSE->null|else S2
bool SELSE(Sstruct &ss)
{
    deal(word.normal);   
    bool ret = true;
    if(word.type!=$else)return true;
    word.readNext();
    deal(word.normal);   
    cout<<"if-then-else语句嵌套"; 
    return S(ss);
}

//SW->while B do S
bool SW(Sstruct &ss)
{
    cout<<"循环语句"<<endl; 
    deal(word.normal);   

    bool ret = true;
    if(word.type!=$while)
    { 
        error("缺少while");
        ret = false;
    }else word.readNext();
    deal(word.normal);   

    Mstruct m1;
    m1.quad = quad;
    Bstruct bs;
    if(!B(bs))return false;

    if(word.type!=$do)
    {
        error("缺少do");
        ret = false;         
    }else word.readNext();
    deal(word.normal);   

    Mstruct m2;
    m2.quad = quad;

    if(!S(ss))return false;
    deal(word.normal);

    int swquad = Nextquad();
    RSS[swquad].setop("j");
    RSS[swquad].setjump(m1.quad);

    backpatch(bs.truelist,m2.quad);
    backpatch(ss.nextlist,m1.quad);
    ss.nextlist = bs.falselist;

    return ret;  
}

//SC->begin Sn end
bool SC(Sstruct &ss)
{
    deal(word.normal);

    bool ret = true;

    if(word.type!=$begin){error("复合语句缺少begin");ret = false;}
    else word.readNext();
    deal(word.normal);

    if(!Sn(ss))ret = false;
    deal(word.normal);

    if(word.type!=$end){error("复合语句缺少end");ret = false;}
    else word.readNext();

    cout<<"复合语句"<<endl; 
    deal(word.normal);     
    return ret;
}

//B->EAEBT|NOT B|(B)BT 
bool B(Bstruct &bs)
{
    deal(word.normal);

    bool ret = true;     
    if(word.type== $left ){
        word.readNext();
        deal(word.normal);

        if(!B(bs))
            return false;

        if(word.type!= $right )
        {
            error("缺少括号");
            ret = false;
        }else {
            word.readNext();
            deal(word.normal);
        }

        if(!BT(bs))
            ret = false;
        deal(word.normal);

    }else if(word.type== $not)
    {
        word.readNext();
        deal(word.normal);
        Bstruct bsa;
        if(!B(bsa))return false;

        bs.falselist = bsa.truelist;
        bs.truelist = bsa.falselist;

    }
    else if(word.type==$flag||word.type==$num)
    {
        Estruct es1;          
        if(!E(es1))return false;

        if(!A())return false;   

        string op = word.att;
        op = "j"+op;      

        word.readNext(); 

        Estruct es2;
        if(!E(es2))return false;

        int quad = Nextquad();
        bs.truelist = quad;

        RSS[quad].setjump(0);
        RSS[quad].setpar1(es1.lexval);
        RSS[quad].setpar2(es2.lexval);
        RSS[quad].setop(op);

        quad = Nextquad();
        bs.falselist=quad;
        RSS[quad].setop("j");
        RSS[quad].setjump(0);

        if(!BT(bs))return false;
    }
    else
    {
        error("语法错误");
        return false;
    }
    return ret;
}

//BT->DB|null 
bool BT(Bstruct &bs)
{
    deal(word.normal);

    if(!D())

        return true;         

    int type = word.type;     
    word.readNext(); 
    deal(word.normal);

    Mstruct mtmp;
    mtmp.quad = quad;

    Bstruct bsa;
    if(!B(bsa)){cout<<"语法错误"<<" "<<word.type<<endl; return false;}

    if(type==$and)
    {
        backpatch(bs.truelist,mtmp.quad);
        bs.falselist = merge(bs.falselist,bsa.falselist);
        bs.truelist = bsa.truelist;                
    }
    else
    {
        backpatch(bs.falselist,mtmp.quad);
        bs.truelist = merge(bs.truelist,bsa.truelist);
        bs.falselist = bsa.falselist;
    }     
    return true;
}

//E->cET|iET|(E)ET
bool E(Estruct &es)
{

    deal(word.normal);

    bool ret = true;     
    if(word.type== $left ){
        word.readNext();
        deal(word.normal);

        if(!E(es))
            return false;

        if(word.type!= $right )
        {
            error("缺少括号");
            ret = false;
        }else {
            word.readNext();
            deal(word.normal);
        }
        if(!ET(es))
            ret = false;
        deal(word.normal);
    }else if(word.type== $flag ||word.type== $num )
    {
        es.lexval = word.att;

        word.readNext();
        deal(word.normal);

        if(!ET(es))return false;
    }
    else
    {
        error("语法错误");
        return false;
    }

    return ret;
}

//ET->CE|null
bool ET(Estruct &es)
{     

    deal(word.normal);

    if(!C())
        return true;

    string op = word.att;

    word.readNext(); 
    deal(word.normal);

    Estruct esa;
    if(!E(esa)){cout<<"语法错误"<<" "<<word.type<<endl; return false;}     

    int quad = Nextquad();     
    RSS[quad].setop(op);
    RSS[quad].setpar1(es.lexval);
    RSS[quad].setpar2(esa.lexval);

    string tmp = NextT();
    RSS[quad].setresult(tmp);

    es.lexval = tmp;

    return true;
}

//A->>|<|=|>=|<=|<>
bool A()
{
    deal(word.normal);
    bool ret = true;
    if(word.type== $gt ||word.type== $lt ||word.type== $eq ||word.type== $goe ||word.type== $loe ||word.type== $ne );
    else {ret = false;}
    return ret; 
}

//C->+|-|*|/;
bool C()
{
    deal(word.normal);

    if(word.type== $add ||word.type== $sub ||word.type== $mul ||word.type== $div )return true;
    else return false; 
}

//D->AND|OR;
bool D()
{
    deal(word.normal);

    if(word.type== $and ||word.type== $or )return true;
    else return false;   
}



int main()
{
    freopen("output.txt","r",stdin);
    freopen("Grammar.out","w",stdout);
    semantic_init();

    word.readNext();
    if(!word.normal){
        cout<<"空文件"<<endl;
        return 0; 
    }

    while(word.type!=$program)
    {
        word.readNext();
        if(!word.normal){
            cout<<"未找到程序头"<<endl;
            return 0; 
        }
        if(word.type!=$program)
        {
            cout<<"语法错误，位置错误"<<endl; 
        }
    }

    if(word.normal)
    {
        P();
    }
    while(word.normal)
    {
        word.readNext();
        if(!word.normal)
        {
            break;
        }
        else
        {
            cout<<"非法字符"<<endl;
        }
    }

    semantic_output();
    return 0;
}


