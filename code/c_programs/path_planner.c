
/*
* EcoMender Bot (EB): Task 2B Path Planner
*
* This program computes the valid path from the start point to the end point.
* Make sure you don't change anything outside the "Add your code here" section.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#define V 32

#ifdef __linux__ // for host pc

    #include <stdio.h>

    void _put_byte(char c) { putchar(c); }

    void _put_str(char *str) {
        while (*str) {
            _put_byte(*str++);
        }
    }

    void print_output(uint8_t num) {
        if (num == 0) {
            putchar('0'); // if the number is 0, directly print '0'
            _put_byte('\n');
            return;
        }

        if (num < 0) {
            putchar('-'); // print the negative sign for negative numbers
            num = -num;   // make the number positive for easier processing
        }

        // convert the integer to a string
        char buffer[20]; // assuming a 32-bit integer, the maximum number of digits is 10 (plus sign and null terminator)
        uint8_t index = 0;

        while (num > 0) {
            buffer[index++] = '0' + num % 10; // convert the last digit to its character representation
            num /= 10;                        // move to the next digit
        }
        // print the characters in reverse order (from right to left)
        while (index > 0) { putchar(buffer[--index]); }
        _put_byte('\n');
    }

    void _put_value(uint8_t val) { print_output(val); }

#else  // for the test device

    void _put_value(uint8_t val) { }
    void _put_str(char *str) { }

#endif

// main function
int main(int argc, char const *argv[]) {

    #ifdef __linux__

        const uint8_t START_POINT   = atoi(argv[1]);
        const uint8_t END_POINT     = atoi(argv[2]);
        uint8_t NODE_POINT          = 0;
        uint8_t CPU_DONE            = 0;

    #else
        // Address value of variables for RISC-V Implementation
        #define START_POINT         (* (volatile uint8_t * ) 0x02000000)
        #define END_POINT           (* (volatile uint8_t * ) 0x02000004)
        #define NODE_POINT          (* (volatile uint8_t * ) 0x02000008)
        #define CPU_DONE            (* (volatile uint8_t * ) 0x0200000c)

    #endif

    // array to store the planned path
    uint8_t path_planned[32];
    // index to keep track of the path_planned array
    uint8_t idx = 0;

    /* Functions Usage

    instead of using printf() function for debugging,
    use the below function calls to print a number, string or a newline

    for newline: _put_byte('\n');
    for string:  _put_str("your string here");
    for number:  _put_value(your_number_here);

    Examples:
            _put_value(START_POINT);
            _put_value(END_POINT);
            _put_str("Hello World!");
            _put_byte('\n');
    */

    // ############# Add your code here #############
    // prefer declaring variable like this
    #ifdef __linux__
        uint32_t graph[32];
        uint8_t distance[32];
        bool visited[32];
        uint8_t unvisited[32];
        uint8_t front = 0;
        uint8_t rear = 0;
        int8_t neighbour[4];
        int8_t weights[4];
        uint8_t prev[32];
        uint8_t node;
        uint32_t current;
    #else
        uint32_t *graph = (uint32_t *) 0x02000010;
        uint8_t *distance = (uint8_t *) 0x02000090;
        uint8_t *unvisited = (uint8_t *) 0x02000B0;
        int8_t *neighbour = (int8_t *) 0x02000D0;
        int8_t *weights = (int8_t *) 0x02000D4;
        uint8_t *prev = (uint8_t *) 0x020000D8;
        uint8_t *front = (uint8_t *) 0x020000F8;
        uint8_t *rear = (uint8_t *) 0x020000F9;
        uint8_t *node = (uint8_t *) 0x02000FA;
        uint8_t *current = (uint8_t *) 0x020000FB;
        uint32_t *visited = (uint32_t *) 0x020000FC;
        
    #endif
    
    graph[ 0] = 0b00001011001100110101001100000000;
                //   00000011001110100100001001001010
    graph[ 1] = 0b00000011010110100001010000000000;
    graph[ 2] = 0b00001100000110100010001000101010;
    graph[ 3] = 0b00010010000000000000000000000000;
    graph[ 4] = 0b00010010000000000000000000000000;
    graph[ 5] = 0b00010010000000000000000000000000;
    graph[ 6] = 0b00000011001110100100001001001010;
    graph[ 7] = 0b00110010000000000000000000000000;
    graph[ 8] = 0b00110010000000000000000000000000;
    graph[ 9] = 0b00110010000000000000000000000000;
    graph[10] = 0b11010011110000100000001101011100;
    graph[11] = 0b01010100000010100110001110011010;
    graph[12] = 0b01011010011101000110100100000000;
    graph[13] = 0b01100001000000000000000000000000;
    graph[14] = 0b01111001100000100110001000000000;
    graph[15] = 0b01110001000000000000000000000000;
    graph[16] = 0b01110010100010011001000100000000;
    graph[17] = 0b10000001000000000000000000000000;
    graph[18] = 0b10000001100110111010100100000000;
    graph[19] = 0b10010011010110101010000100000000;
    graph[20] = 0b10011001000000000000000000000000;
    graph[21] = 0b10010010101100011011101000000000;
    graph[22] = 0b10101001000000000000000000000000;
    graph[23] = 0b11110001110000111010101000000000;
    graph[24] = 0b11001001101110110101001000000000;
    graph[25] = 0b11000001000000000000000000000000;
    graph[26] = 0b01010011110110011110010000000000;
    graph[27] = 0b11010001000000000000000000000000;
    graph[28] = 0b11010100111010011111001000000000;
    graph[29] = 0b11100001000000000000000000000000;
    graph[30] = 0b11111001111000101011100100000000;
    graph[31] = 0b11110001000000000000000000000000;

    // graph[0] = 1;

    // distance[0] = 0b00000000;
    // distance[31] = 0b11111111;

    // unvisited[0] = 25;
    // unvisited[31] = 26;

    // neighbour[0] = 5;
    // neighbour[3] = 6;

    // weights[0] = 1;
    // weights[3] = 5;

    // prev[0] = 10;
    // prev[31] = 11;



    // *front = 1;
    // *rear = 0;
    // *node = 15;

    // *visited = 1;

    // *current = 5;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
    *front = 0;
    *rear = 0;

    // unvisited[rear] = START_POINT;
    // rear = (rear + 1) % V;

    // void enqueue(uint8_t value){
        // unvisited[*rear] = value;
        // *rear = (*rear + 1) % V;
    // }

    // uint8_t dequeue(){
        // uint8_t value = unvisited[*front];
        // *front = (*front + 1) % V;
        // return value;
    // }

    // enqueue(START_POINT);
        unvisited[*rear] = START_POINT;
        *rear = (*rear + 1) % V;

    for(int8_t i = 0; i < V; i++){
        distance[i] =  INT8_MAX;
    }
        *visited = 0;

    distance[START_POINT] = 0;

    while(*front != *rear){
        // *node = dequeue();
        *node = unvisited[*front];
        *front = (*front + 1) % V;
        // return value;
        
        // visited[*node] = true;

        *visited |= (1 << *node);
        for (int8_t i = 0; i < 4; i++){
            neighbour[i] = (graph[*node] >> (27 - (i*8)) & 31);
            weights[i] = (graph[*node] >> (24 - (i*8)) & 7);
            if(neighbour[i]==0 && weights[i]==0){
                neighbour[i] = -1;
                weights[i] = -1;
            }
            if((*visited & (1 << *node)) && neighbour[i]!=-1){
                // enqueue(neighbour[i]);
                unvisited[*rear] = neighbour[i];
                *rear = (*rear + 1) % V;
                if (distance[*node] + weights[i] < distance[neighbour[i]]){
                    distance[neighbour[i]] = distance[*node] + weights[i];
                    prev[neighbour[i]] = *node;
                }
            }
        }
    }

    *current = END_POINT;
    while (*current != START_POINT){
        path_planned[idx++] = *current;
        *current = prev[*current];
    }

    path_planned[idx++] = START_POINT;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ##############################################

    // the node values are written into data memory sequentially.
    for (int i = idx-1; i >= 0; --i) {
        NODE_POINT = path_planned[i];
    }
    // Path Planning Computation Done Flag
    CPU_DONE = 1;

    #ifdef __linux__    // for host pc

        _put_str("######### Planned Path #########\n");
        for (int i = idx-1; i >= 0; i--) {
            _put_value(path_planned[i]);
        }
        _put_str("################################\n");

    #endif

    return 0;
}

