/*
SECR2043-03 OPERATING SYSTEMS
Semester 2, 2020/2021
Group 8
Student Name:	SEE WEN XIANG	 		A19EC0206
				AIMAN ARRIADY BIN AZMAN A19EC0180
				ABU SAYED KHUDRI ROMAN 	A19EC4002
Project OS */ 
#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h>
 
using namespace std;
struct processSJF
{
	int pid;
	int btime;
	int atime;
};
bool SJFBurstTimeSort(processSJF a,processSJF b){
    return a.btime < b.btime; 
}
bool SJFArrivalTimeSort(processSJF a,processSJF b){
    return a.atime < b.atime; 
}
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};
void sjf(){
	processSJF a[1000];
	int n;
	system ("cls");
	cout<<"\nShortest-Job First Scheduling Food Ordering System"<<endl;
	cout<<"\nEnter the Total Number of Orders: ";
    cin>>n;
	for(int j = 0; j < n; j++) {
    	cout<<endl;
        cout<<"Enter Arrival Time of Order "<<j+1<<": ";
        cin>>a[j].atime;
        cout<<"Enter Cooking Time of Order "<<j+1<<" (in minutes): ";
        cin>>a[j].btime;
        a[j].pid = j+1;
    }
	sort(a,a+n,SJFBurstTimeSort);
    sort(a,a+n,SJFArrivalTimeSort);
	
	 int ttime=0,i;
    int j,tArray[n];
    for(i=0;i<n;i++){
        j=i;
        while(a[j].atime<=ttime&&j!=n){
            j++;
        }
        sort(a+i,a+j,SJFBurstTimeSort);
        tArray[i]=ttime;
        ttime+=a[i].btime;
    }
    tArray[i] = ttime;
    float averageWaitingTime=0;
    float averageResponseTime=0;
    float averageTAT=0;

    cout<<left<<setw(15)<<"\n#Order ID"<<setw(15)<<"Arrival Time"<<setw(20)<<"Cooking Time"<<setw(20)<<"Completion Time"<<setw(25)<<"TurnAround Time"<<setw(20)<<"Waiting Time";

    int index=1;

    while (index<=n){
		for (int i=0;i<n;i++)
		{
		if (a[i].pid==index){
		int turnaround=0,waiting=0;
				if((tArray[i]-a[i].atime)<0)
		{
			waiting=0;
		}
		else
		{
			waiting=tArray[i]-a[i].atime;
		}
		turnaround=waiting+a[i].btime;

        cout <<left<<"\nO["<<a[i].pid<<setw(15)<<"]"<<setw(15)<<a[i].atime <<setw(20)<< a[i].btime<<setw(20)<<tArray[i+1]<<setw(25)<<turnaround<<setw(20)<<waiting;
        averageTAT+=turnaround;
        averageWaitingTime+=waiting;
    }
    }
    index++;
	}
	cout<<fixed<<setprecision(2);
    cout<<endl<<endl<<"Average Waiting Time = "<<(float)averageWaitingTime/(float)n<<" (min)"<<endl;
    cout<<"Average Turnaround Time = "<<(float)averageTAT/(float)n<<" (min)"<<endl;
}
void srtf(){
	int n;
    struct process p[1000];
    double avg_turnaround_time, avg_waiting_time;
    
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    
    int total_idle_time = 0;
   
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(2) << fixed;
	system ("cls");
	cout<<"\nShortest-Remaining Time First Food Ordering System"<<endl;
    cout<<"\nEnter Total number of Orders: ";
    cin>>n;
	cin.ignore();
    for(int i = 0; i < n; i++) {
    	cout<<endl;
        cout<<"Enter Arrival Time of Order "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter Cooking Time of Order "<<i+1<<"(in minutes): ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        burst_remaining[i] = p[i].burst_time;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(burst_remaining[i] < mn) {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if(burst_remaining[i] == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;
            
            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }  
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    cout<<endl<<left<<setw(15)<<"#Order ID"<<setw(15)<<"Arrival Time"<<setw(15)<<"Cooking Time"<<setw(15)<<"Start Time"<<setw(20)<<"Completion Time"<<setw(20)<<"Turnaround Time"<<setw(15)<<"Waiting Time";

    for(int i = 0; i < n; i++) {
        cout<<"\nO["<<p[i].pid<<setw(15)<<"]"<<setw(15)<<p[i].arrival_time<<setw(15)<<p[i].burst_time<<setw(15)<<p[i].start_time<<setw(20)<<p[i].completion_time<<setw(20)<<p[i].turnaround_time<<setw(15)<<p[i].waiting_time;
    }
    cout<<endl<<"\nAverage Waiting Time = "<<avg_waiting_time<<" (min)"<<endl;
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<" (min)"<<endl;    
}

void priority(){
	int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,pos,temp;
	double total=0,avg_wt,avg_tat;
	system ("cls");
	cout<<"\nPriority Scheduling Food Ordering System"<<endl;
    cout<<"\nEnter Total Number of Orders: ";
    cin>>n;
 	cin.ignore();
    cout<<"\nEnter Cooking Time and Priority\n";
    for(i=0;i<n;i++)
    {
        cout<<"\nOrder["<<i+1<<"]\n";
        cout<<"Cooking Time (in minutes): ";
        cin>>bt[i];
        cout<<"Priority: ";
        cin>>pr[i];
        p[i]=i+1;           //contains process number
    }
 
    //sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }
 
        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
 
    wt[0]=0;            //waiting time for first process is zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=(float)total/(float)n;      //average waiting time
 	total=0;
    cout<<endl<<left<<setw(15)<<"#Order ID"<<setw(15)<<"Cooking Time"<<setw(15)<<"Waiting Time"<<setw(15)<<"Turnaround Time";
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        cout<<"\nO["<<p[i]<<setw(15)<<"]"<<setw(15)<<bt[i]<<setw(15)<<wt[i]<<setw(15)<<tat[i];
    }
 
    avg_tat=(float)total/(float)n;     //average turnaround time
    cout<<fixed<<setprecision(2);
    cout<<"\n\nAverage Waiting Time = "<<avg_wt<<" (min)";
    cout<<"\nAverage Turnaround Time = "<<avg_tat<<" (min)"<<endl;
}
void menu(){
	system ("cls");
	cout<<"<<<<< WELCOME TO AUTOMATED FOOD ORDERING SYSTEM (SJF, SRTF, PRIORITY) >>>>>>"<<endl<<endl;
	cout<<"System's Purposes: "<<endl;
	cout<<"i.	To minimize customer waiting time and turnaround time by using different algorithms of process scheduling."<<endl;
	cout<<"ii.	To discover the best efficient algorithm among this three process scheduling algorithms."<<endl<<endl;
	cout<<"Menu"<<endl;
	cout<<"[1] Shortest-Job First Scheduling"<<endl;
	cout<<"[2] Shortest-Remaining Time First"<<endl;
	cout<<"[3] Priority Scheduling"<<endl;
	cout<<"[4] Exit"<<endl;
}

int main()
{
	int choice;
	here:
	menu();
  	do{
  	try {
	cout<<"Choice (1-4): ";
    cin>>choice;
    
    if (choice==1||choice==2||choice==3||choice==4) {
    } else {
      throw (choice);
    }
  	}
	  catch (int myNum) {
	    cout << "Access denied - You must enter correct input.\n";
	  }	
	}while(choice!=1&&choice!=2&&choice!=3&&choice!=4);
	  
	
	cin.ignore();
	switch (choice){
		case 1:	sjf();
				system("PAUSE");
				goto here;
		case 2:	srtf();
				system("PAUSE");
				goto here;
		case 3:	priority();
				system("PAUSE");
				goto here;
		default: break;
	}
	return 0;
}
