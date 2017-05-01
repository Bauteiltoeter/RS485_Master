#include "segmentdisplay.h"
#include <QBrush>
#include <QPainter>
#include <math.h>

static uint16_t charset[256] = {
    //utsrpnmkhgfedcba
    0b0100010011111111,		//0
    0b0000010000001100,		//1
    0b1000100001110111,		//2
    0b0000100000111111,		//3
    0b1000100010001100,		//4
    0b1000100010111011,		//5
    0b1000100011111000,		//6
    0b0000000000001111,		//7
    0b1000100011111111,		//8
    0b1000100010111111,		//9
    0b1000100011001111,		//a
    0b0010101000111111,		//b
    0b0000000011110011,		//c
    0b0010001000111111,		//d
    0b1000000011110011,		//e
    0b1000000011000011,		//f
    0b0000100011111011,		//g
    0b1000100011001100,		//h
    0b0010001000110011,		//i
    0b0000000001111100,		//j
    0b1001010011000000,		//k
    0b0000000011110000,		//l
    0b0000010111001100,		//m
    0b0001000111001100,		//n
    0b0000000011111111,		//o
    0b1000100011000111,		//p
    0b0001000011111111,		//q
    0b1001100011000111,		//r
    0b1000100010111011,		//s
    0b0010001000000011,		//t
    0b0000000011111100,		//u
    0b0100010011000000,		//v
    0b0101000011001100,		//w
    0b0101010100000000,		//x
    0b0010010100000000,		//y
    0b0100010000110011,		//z
    0b0000000000000000,		//Space   ASCII-Table from ' ' to '/'
    0b0000000000000000,		//!
    0b0000001000000100,		//"
    0b1010101000111100,		//#
    0b1010101010111011,		//$
    0b1110111010011001,		//%
    0b0000000000000000,		//&
    0b0000000000000000,		//bank
    0b0010001000010010,		//(
    0b0010001000100001,		//)
    0b1111111100000000,		//*
    0b1010101000000000,		//+
    0b0010000000000000,		//,
    0b1000100000000000,		//-
    0b0000000000010000,		//.
    0b0100010000000000,		// /
    0b0000101000000110,		// �
    0b1111111111111111
};

SegmentDisplay::SegmentDisplay()
{

}

void SegmentDisplay::paint(QPainter *painter)
{
    setWidth(floor(height()*0.722));
    double scaling = height()/100;

    QBrush brush(QColor("#505050"));
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawRect(0+x(), 0+y(), width(), height() );



    QBrush brush2(QColor("#FFFF00"));

    QPen inactivePen( QColor("#202020"));
    inactivePen.setWidth(5*scaling);

    QPen activePen( Qt::red );
    activePen.setWidth(5*scaling);


    painter->setBrush(brush2);

    painter->setPen(inactivePen);
    for(int i=0; i < 16; i++)
    {
        if(!segments[i])
            drawSegment(i,scaling,painter);
    }
    painter->setPen(activePen);
    for(int i=0; i < 16; i++)
    {
        if(segments[i])
            drawSegment(i,scaling,painter);
    }

}

int SegmentDisplay::character()
{
    return ' ';
}

void SegmentDisplay::setCharacter(char c)
{
    uint16_t bits = charset[ascii_to_index(c)];


    for(uint8_t i=0; i<16; i++)
    {

        if(bits & (1UL<<i))
        {
            segments[i] = 1;
        }
        else
        {
            segments[i] = 0;
        }
    }
}

uint8_t SegmentDisplay::ascii_to_index(char ascii)
{
    if(ascii >= '0' && ascii <= '9')
    {
        return ascii-'0';
    }
    if(ascii>='a' && ascii <= 'z')
    {
        return ascii-'a' + 10; //get index of a and add 10 because of numbers
    }
    if(ascii>='A' && ascii <='Z')
    {
        return ascii-'A' + 10; //get index of a and add 10 because of numbers
    }
    if(ascii>=' ' && ascii <='/')
    {
        return ascii-' ' + 36;
    }

    if(ascii=='\0')
        return ascii_to_index(' ');

    if(ascii=='ä')
        return 52;

    if(ascii=='~')
        return 53;

    return 0;
}

void SegmentDisplay::drawSegment(int segment, double scaling, QPainter* painter)
{
    QPointF a(20*0.7*scaling+x(),15*scaling+y());
    QPointF b(55*0.7*scaling+x(),15*scaling+y());
    QPointF c(90*0.7*scaling+x(),15*scaling+y());

    QPointF h(15*0.7*scaling+x(),50*scaling+y());
    QPointF i(50*0.7*scaling+x(),50*scaling+y());
    QPointF d(85*0.7*scaling+x(),50*scaling+y());

    QPointF g(10*0.7*scaling+x(),85*scaling+y());
    QPointF f(45*0.7*scaling+x(),85*scaling+y());
    QPointF e(80*0.7*scaling+x(),85*scaling+y());

    switch(segment)
    {
        case 0: painter->drawLine(a,b); break;
        case 1: painter->drawLine(b,c); break;
        case 2: painter->drawLine(c,d); break;
        case 3: painter->drawLine(d,e); break;
        case 4: painter->drawLine(e,f); break;
        case 5: painter->drawLine(f,g); break;
        case 6: painter->drawLine(g,h); break;
        case 7: painter->drawLine(h,a); break;
        case 8: painter->drawLine(a,i); break;
        case 9: painter->drawLine(b,i); break;
        case 10: painter->drawLine(c,i); break;
        case 11: painter->drawLine(d,i); break;
        case 12: painter->drawLine(e,i); break;
        case 13: painter->drawLine(f,i); break;
        case 14: painter->drawLine(g,i); break;
        case 15: painter->drawLine(h,i); break;
    }
}
