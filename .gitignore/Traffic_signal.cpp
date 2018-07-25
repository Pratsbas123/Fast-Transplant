/*
    The following code is a suggested modification to the already existing traffic signal system.
    This is used to generate simulations to complement the project architectures.
    Author: Sobhan Mondal
*/
#include<bits/stdc++.h>
using namespace std;

// Function for calculating real time duration
void delay(float number_of_seconds)
{
    int milli_seconds = (int)((float)1000 * number_of_seconds);
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

int main()
{
    srand(time(NULL));

    int speed, distance, no_of_signal, signal_duration, time;

    // Input will be given by the system

    distance = 12000; // Distance from donor hospital to recipient hospital
    no_of_signal = 10; // No of traffic signal through the path
    signal_duration = 30; // General traffic signal duration like - RED : , GREEN :
    //int signal_distance[10] = {2000,450,350,1400,350,500,700,4000,2000,250}; // Consecutive distance between two traffic signal
    int signal_distance[10] = {1500,450,350,700,350,500,700,1000,200,250};

    int i, j, state, signal_clock[10], temp = 0, flag[10], flag_red[10], flag_green[10];
    char signal_state[10];

    for(i=0;i<10;i++)
    {
        signal_distance[i] = signal_distance[i] + temp;
        temp = signal_distance[i];
    }

    // Initializing all the signals by the state - Red or Green and their signal duration by using rand()
    for(i=0;i<10;i++)
    {
        signal_clock[i] = rand()%30;
        state = rand()%100;
        if(state>50)
            signal_state[i] = 'G';
        else
            signal_state[i] = 'R';
    }

    delay(2);

    fill(flag,flag+10,0);
    fill(flag_red,flag_red+10,0);
    fill(flag_green,flag_green+10,0);
    time = 0;

    for(i=1;i<=10;i++)
        cout <<"D"<<i<<"\t";
    for(i=1;i<=10;i++)
        cout <<"S"<<i<<"\t";
    cout <<"Time\n";

    // code that simulate real world traffic system with the proposed system that creates the green zone
    while (distance >= 0)
    {
        /* Speed of the ambulance : For ease of simulation here the speed is taken as a range between 54km/h to 90km/h
           In real world scenario speed will be updated from the system */
        speed = 15 + rand()%10;
        distance = distance - speed;

        for(i=0;i<10;i++)
        {
            signal_distance[i] = signal_distance[i] - speed;
            if(signal_distance[i]<=0)
                cout <<"CROSSED"<<"\t";
            else
                cout <<signal_distance[i]<<"\t";


            if(signal_distance[i] < 1400 && flag[i] == 0) // 1400 is the range from a signal for efficient signal state & timing changing
            {
                flag[i] = 1;
                if(signal_state[i]=='R')
                    flag_red[i] = 1;
                else
                    flag_green[i] = 1;
            }

            if(flag_red[i] == 1)
            {
                signal_clock[i]--;
                if(signal_clock[i] <= 0)
                {
                    signal_clock[i] = 100;
                    signal_state[i] = 'G';
                    flag_red[i] = 0;
                }
            }
            if(flag_green[i] == 1)
            {
                signal_clock[i]--;
                if(signal_clock[i] <= 0)
                {
                    signal_clock[i] = 20;
                    signal_state[i] = 'R';
                    flag_red[i] = 1;
                    flag_green[i] = 0;
                }
            }
            if(flag_red[i] != 1 && flag_green[i] != 1)
            {
                signal_clock[i]--;
                if(signal_clock[i] <= 0)
                {
                    signal_clock[i] = 30;

                    if(signal_state[i] == 'G')
                        signal_state[i] = 'R';
                    else
                        signal_state[i] = 'G';

                }
            }

        }

        for(i=0;i<10;i++)
            cout <<signal_state[i]<<"-"<<signal_clock[i]<<"\t";

        time++;

        cout <<time<<"\n";
        //delay(1); // use time for simulation
        if(signal_distance[9]<=-5)
            exit(0);
    }
}
