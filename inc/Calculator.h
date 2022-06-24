#ifndef CALCUALTOR
#define CALCULATOR
#define RAYGUI_IMPLEMENTATION

#include <string>
#include "Widget.h"

#include <raylib.h>
#include <iostream>
#include <ctime>
#include "Constants.h"
#include <stack>
#include <list>
#include <cmath>
#include <iomanip>
using namespace std;

class Calculator : public Widget {
private:
 std::string text;
 Vector2 mousePoint;
 Texture2D plusButton;
 bool Button1Pressed;
 int offset;
 int lastOperatorIndex;
 stack<char> operators;
 stack<float> operands;
public:
    Calculator(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string n) :
        Widget (x, y, w, h, n) {
        // Calls widget's constructor
        //render = false;
        text = "";
        mousePoint = { 0.0f , 0.0f };
        Image plusIcon = LoadImage( "../resources/images/plus_operator.png" );
        ImageResize( &plusIcon, 50, 50);
        plusButton = LoadTextureFromImage(plusIcon);
        UnloadImage(plusIcon);
        Button1Pressed = false;
        offset = 25;
        
    }
private:    
    void spawnButton(int x, int y, int w,int h, std::string buttonText){
        DrawRectangleLines(x,y,w,h,SKYBLUE);
        int buttonOffset = (50 - MeasureText(buttonText.c_str(),30))/2;
        DrawText(buttonText.c_str(), buttonOffset+x, 10 + y, 30, SKYBLUE);
    }
private:
    bool buttonInteract(int x, int y, int w,int h, std::string buttonText){

        if (CheckCollisionPointRec(mousePoint, (Rectangle){x,y,w,h})){

            DrawRectangle(x,y,w,h,SKYBLUE);
            int buttonOffset = (50 - MeasureText(buttonText.c_str(),30))/2;
            DrawText(buttonText.c_str(), buttonOffset+x, 10 + y, 30, BLACK);

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) return true;
            else return false;

        }
        

    }


private:
int precedence(char op){
    if(op == '+'||op == '-') return 1;
    if(op == '*'||op == '/') return 2;
    if(op == '^') return 3;
    return 0;
}
 
// Function to perform arithmetic operations.
private:
 float applyOp(float a, float b, char op){

    if ( op == '+') return a+b;
    else if ( op == '-') return a-b;
    else if (op == '*') return a*b;
    else if (op == '/') return a/b;
    else if (op == '^') return pow(a,b);  
    
}
 
// Function that returns value of
// expression after evaluation.
private:
float evaluate(string tokens){
    int i;
     
    // stack to store integer values.
    stack <float> values;
     
    // stack to store operators.
    stack <char> ops;
     
    for(i = 0; i < tokens.length(); i++){
         
        // Current token is a whitespace,
        // skip it.
        if(tokens[i] == ' ')
            continue;
         
        // Current token is an opening
        // brace, push it to 'ops'
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }
         
        // Current token is a number, push
        // it to stack for numbers.
        else if(isdigit(tokens[i]) ){
            float val = 0.0f;
            std::string tokenVal = "";
            // There may be more than one
            // digits in number.
            while(i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.'))
            {
                tokenVal += tokens[i];
               
                i++;
            }
              val = std::stof(tokenVal);
            values.push(val);
             
            // right now the i points to
            // the character next to the digit,
            // since the for loop also increases
            // the i, we would skip one
            //  token position; we need to
            // decrease the value of i by 1 to
            // correct the offset.
              i--;
        }
         
        // Closing brace encountered, solve
        // entire brace.
        else if(tokens[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                float val2 = values.top();
                values.pop();
                 
                float val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
             
            // pop opening brace.
            if(!ops.empty())
               ops.pop();
        }
         
        // Current token is an operator.
        else
        {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
            while(!ops.empty() && precedence(ops.top())
                                >= precedence(tokens[i])){
                float val2 = values.top();
                values.pop();
                 
                float val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
             
            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }
     
    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    while(!ops.empty()){
        float val2 = values.top();
        values.pop();
                 
        float val1 = values.top();
        values.pop();
                 
        char op = ops.top();
        ops.pop();
                 
        values.push(applyOp(val1, val2, op));
    }
     
    // Top of 'values' contains result, return it.
    return values.top();
}


//
private: 
    void draw() override {

        // Put code here for drawing!
        int32_t middle_x =  pos_x + (width / 2); //posx => parameter in Widget
        int32_t middle_y =  pos_y ;

        mousePoint = GetMousePosition();

        //checks if mouse is over the caluclator widget , the if block can be removed if the calc needs to be static
        if (CheckCollisionPointRec(mousePoint, (Rectangle){pos_x, pos_y, CALC_W, CALC_H }) ){
       
        int textWidth = MeasureText(text.c_str(), 30);
        
        uint32_t x_cord = middle_x - (textWidth / 2);
        DrawText(text.c_str(), x_cord, middle_y + 20, 30, SKYBLUE);
        
      
        Rectangle button_op1 = {x_cord , middle_y + 80, 50, 50};
        
        
        //column 1
        spawnButton(offset +pos_x, middle_y  + 100 , 50,50, "1");
        spawnButton(offset +pos_x, middle_y  + 150 , 50,50, "4");
        spawnButton(offset +pos_x, middle_y  + 200 , 50,50, "7");
        spawnButton(offset +pos_x, middle_y  + 250 , 50,50, "+");
        spawnButton(offset +pos_x, middle_y  + 300 , 50,50, "-");
        spawnButton(offset +pos_x, middle_y  + 350 , 50,50, "^");
        spawnButton(offset +pos_x, middle_y  + 400 , 50,50, "CE");

        //column 2
        spawnButton(offset +pos_x + 50, middle_y  + 100 , 50,50, "2");
        spawnButton(offset +pos_x + 50, middle_y  + 150 , 50,50, "5");
        spawnButton(offset +pos_x + 50, middle_y  + 200 , 50,50, "8");
        spawnButton(offset +pos_x + 50, middle_y  + 250 , 50,50, "0");
        spawnButton(offset +pos_x + 50, middle_y  + 300 , 50,50, "/");
        spawnButton(offset +pos_x + 50, middle_y  + 350 , 50,50, "*");
        spawnButton(offset +pos_x + 50, middle_y  + 400 , 50,50, "C");

        //column 3
        spawnButton(offset +pos_x + 100, middle_y  + 100 , 50,50, "3");
        spawnButton(offset +pos_x + 100, middle_y  + 150 , 50,50, "6");
        spawnButton(offset +pos_x + 100, middle_y  + 200 , 50,50, "9");
        spawnButton(offset +pos_x + 100, middle_y  + 250 , 50,50, "(");
        spawnButton(offset +pos_x + 100, middle_y  + 300 , 50,50, ")");
        spawnButton(offset +pos_x + 100, middle_y  + 350 , 50,50, ".");
        spawnButton(offset +pos_x + 100, middle_y  + 400 , 50,50, "=");

        //****************************hover*************************

        //column 1
        if(buttonInteract(offset +pos_x, middle_y  + 100 , 50,50, "1")){text += "1";}
        if(buttonInteract(offset +pos_x, middle_y  + 150 , 50,50, "4")){text += "4";}
        if(buttonInteract(offset +pos_x, middle_y  + 200 , 50,50, "7")){text += "7";}
        if(buttonInteract(offset +pos_x, middle_y  + 250 , 50,50, "+") && (isalnum(text.c_str()[text.length()-1]) || text.c_str()[text.length()-1] == ')' ) )
        { text += "+"; }
        if(buttonInteract(offset +pos_x, middle_y  + 300 , 50,50, "-") && (isalnum(text.c_str()[text.length()-1]) || text.c_str()[text.length()-1] == ')' ))
        { text += "-"; }
        if(buttonInteract(offset +pos_x, middle_y  + 350 , 50,50, "^") && (isalnum(text.c_str()[text.length()-1]) || 
        text.c_str()[text.length()-1] == ')' ))
        { text += "^"; }
        if(buttonInteract(offset +pos_x, middle_y  + 400 , 50,50, "CE"))
        { text = ""; }

        //column 2
        if(buttonInteract(offset +pos_x + 50, middle_y  + 100 , 50,50, "2")){text += "2";}
        if(buttonInteract(offset +pos_x + 50, middle_y  + 150 , 50,50, "5")){text += "5";}
        if(buttonInteract(offset +pos_x + 50, middle_y  + 200 , 50,50, "8")){text += "8";}
        if(buttonInteract(offset +pos_x + 50, middle_y  + 250 , 50,50, "0")){text += "0";}
        if(buttonInteract(offset +pos_x + 50, middle_y  + 300 , 50,50, "/") && (isalnum(text.c_str()[text.length()-1]) || text.c_str()[text.length()-1] == ')' ))
        { text += "/"; }
        if(buttonInteract(offset +pos_x + 50, middle_y  + 350 , 50,50, "*" ) && isalnum(text.c_str()[text.length()-1]))
        { text += "*"; }
        if(buttonInteract(offset +pos_x + 50, middle_y  + 400 , 50,50, "C"))
        {text = text.substr(0, text.length() -1);}

        //column 3
        if(buttonInteract(offset +pos_x + 100, middle_y  + 100 , 50,50, "3")){text += "3";}
        if(buttonInteract(offset +pos_x + 100, middle_y  + 150 , 50,50, "6")){text += "6";}
        if(buttonInteract(offset +pos_x + 100, middle_y  + 200 , 50,50, "9")){text += "9";}

        if(buttonInteract(offset +pos_x + 100, middle_y  + 250 , 50,50, "(") && 
        !isalnum(text.c_str()[text.length()-1]))
        { text += "("; }
        if(buttonInteract(offset +pos_x + 100, middle_y  + 300 , 50,50, ")") &&
         isalnum(text.c_str()[text.length()-1]))
         { text += ")"; }
        if(buttonInteract(offset +pos_x + 100, middle_y  + 350 , 50,50, ".") && 
        isalnum(text.c_str()[text.length()-1]))
        { text += "."; }
        if(buttonInteract(offset +pos_x + 100, middle_y  + 400 , 50,50, "=")){
            
            float resultEval = evaluate(text);
            
            int int_resultEval = round(resultEval * 100);
            std::string str_resultEval = std::to_string(int_resultEval);
            text = str_resultEval.substr(0, str_resultEval.length() - 2) + "." + 
            str_resultEval.substr( str_resultEval.length() - 2, str_resultEval.length() - 1);
        
        }
        }
     else{

        int hoverTextWidth;
        std::string text_display = "CALCULATOR";

        hoverTextWidth = MeasureText(text_display.c_str(), 20);
        uint32_t x_cord = middle_x - (hoverTextWidth / 2);


        DrawText(text_display.c_str(), x_cord + 10, middle_y + 40, 20, SKYBLUE);
        
        DrawRectangleLines(x_cord, middle_y + 20, hoverTextWidth + 20, 50, SKYBLUE);
        
        }
    }

private:

};

#endif