#include "display.h"

Display::Display()
{
    _rows =0;
    _columns=0;
}



void Display::paint(QPainter *painter)
{
    if(displays.size()>0)
    {
        setWidth( (displays.first()->width()+2)*_columns);
        setHeight((displays.first()->height()+2)*_rows);
        for(int i=0; i < displays.size(); i++)
        {
            displays[i]->setHeight(100);
            displays[i]->setX( (i%_columns) *(displays[i]->width()+2));
            displays[i]->setY( (i/_columns) *(displays[i]->height()+2));

            displays[i]->paint(painter);
        }
    }



}

int Display::columns()
{

}

int Display::rows()
{

}

QString Display::text()
{

}

void Display::setRows(int r)
{
    _rows = r;
    updateList();
}

void Display::setColumns(int c)
{
    _columns = c;
    updateList();
}

void Display::setContent(QByteArray content)
{
    qDebug() << "Updating content";

    for(int i=0; i < displays.size() && i < content.size()
        ; i++)
    {
        qDebug() << "Char " << i << "content: " << content.at(i);
        displays[i]->setCharacter(content.at(i) );
    }

    update();
}


void Display::updateList()
{
    int diff = displays.size() - (_rows*_columns);

    if(diff > 0) {
        //mehr displays als
        for(int i=0; i< diff; i++) {
            delete displays.last();
            displays.removeLast();
        }
    }
    else if(diff < 0) {
        //mehr displays als
        for(int i=0; i< -diff; i++) {
            displays.append(new SegmentDisplay);
        }
    }
}
