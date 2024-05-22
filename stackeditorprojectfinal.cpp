#include <iostream>
using namespace std;

class Stack {
private:
    char oper[100]; 
    char charac[100]; 
    int pos[100];   
    int top;

public:
    Stack() : top(-1) {}

    void push(char o, char c, int p )
	{ if (top < 99) {
      top++;
      oper[top] = o;  
     charac[top] = c;               
      pos[top] = p;
        }
    }

    void pop() 
	{  if (top >= 0) {
       top--;
       }
    }

    char topoper() 
	 {  if (top >= 0) {
        return oper[top];
    }
      return 0;
    }

    char topchar() 
	 {  if (top >= 0) {
        return charac[top];
    }
       return 0;  
    }

    int toppos() 
	 {  if (top >= 0) {
        return pos[top];
      }
     return -1; 
    }

    bool isempty() 
	 {  return top == -1;
    }
};

class Texteditor
 {   private:
    char text[100];  
    int textlen;  
    Stack undost; 
    Stack redost;  
    int cursorpos;

public:
    Texteditor() : textlen(0), cursorpos(0) {}

    void insert(char c) 
	{ for (int i = textlen; i > cursorpos; --i) 
	    {   text[i] = text[i - 1];
           }
        text[cursorpos] = c;
        textlen++;
        cursorpos++;
        undost.push('i', c, cursorpos - 1);
        while (!redost.isempty()) redost.pop();
    }

    void remove()
	 {    if (cursorpos > 0)
    { char deletedchar = text[cursorpos - 1];  
       for (int i = cursorpos - 1; i < textlen - 1; ++i) 
		{ text[i] = text[i + 1]; 
           }
       textlen--;
       cursorpos--;
       undost.push('d', deletedchar, cursorpos);
       while (!redost.isempty()) redost.pop();
        }
    }

    void undo() {
        if (!undost.isempty())
	 { char oper = undost.topoper();
       char charac = undost.topchar();
      int pos = undost.toppos();
       undost.pop();
        if (oper == 'i') {
       for (int i = pos; i < textlen - 1; ++i)
	    {
        text[i] = text[i + 1];
         }
           textlen--;
           cursorpos = pos;
           redost.push('i', charac, pos);
            }
	   else if (oper == 'd')
	   {  for (int i = textlen; i > pos; --i) {
            text[i] = text[i - 1];
        }
        text[pos] = charac;
        textlen++;
         cursorpos = pos + 1;
        redost.push('d', charac, pos);
            }
        }
    }

    void redo() {
        if (!redost.isempty())
    {  char oper = redost.topoper();
       char charac = redost.topchar();
       int pos = redost.toppos();
       redost.pop();
        if (oper == 'i') {
        for (int i = textlen; i > pos; --i) 
		{ text[i] = text[i - 1];
           }
        text[pos] = charac;
        textlen++;
        cursorpos = pos + 1;
        undost.push('i', charac, pos);
        } else if (oper == 'd')
		 { for (int i = pos; i < textlen - 1; ++i) {
            text[i] = text[i + 1];
        }
        textlen--;
        cursorpos= pos;
        undost.push('d', charac, pos);
          }
        }
    }

    void next() {
        if (cursorpos < textlen) {
        cursorpos++;
        }
    }

    void prev() {
        if (cursorpos > 0) {
        cursorpos--;
        }
    }

    void start() {
        cursorpos = 0;
    }

    void end() {
        cursorpos = textlen;
    }

    int curr_pos()  {
        return cursorpos;
    }

    void display() {
        cout << "Text: ";
        for (int i = 0; i < textlen; ++i) {
        cout << text[i];
        }
        cout << endl;
    }
};

int main() {
    Texteditor e;

    e.insert('w');
    e.insert('o');
    e.insert('r');
    e.insert('l');
    e.insert('d');
    e.display();

    e.undo();
    e.display();
    e.undo();
    e.display(); 

    e.redo();
    e.display(); 
    e.redo();
    e.display(); 

    return 0;
}
