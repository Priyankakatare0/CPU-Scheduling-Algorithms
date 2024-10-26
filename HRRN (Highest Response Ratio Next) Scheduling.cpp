#include<bits/stdc++.h>
using namespace std;

//Implement HRRN Algorithm
class Process{
public:
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	int rt;
	// bool isready;

	Process(int i,int j,int k){
		pid=i;
		at=j;
		bt=k;
		ct=-1;
		tat=-1;
		wt=-1;
		rt=bt;
		// isready=false;
	}

};

int cur_time=0;

//custom comparator for sorting
bool cmp_at(Process* p1,Process* p2){
   if(p1->at>p2->at)return false;
   if(p1->at==p2->at){
     if(p1->pid>p2->pid)return false;
   }
   return true; 
}

//custom comparator for priority_queue
class Compare{
public:
    bool operator()(Process* p1,Process* p2){
         if(ResponseRatio(p1)<ResponseRatio(p2))return true;
        if(ResponseRatio(p1)==ResponseRatio(p2)){
           if(p1->at>p2->at)return true;
            if(p1->at==p2->at){
            if(p1->pid>p2->pid)return true;
     }
    }
    return false;
    }

    float ResponseRatio(Process* p1){
    int w=cur_time-p1->at+p1->bt;
    return (float)w/p1->bt;
   
}
};

void generateParams(vector<Process*>&process){
    for(int i=0;i<process.size();i++){
        process[i]->tat=process[i]->ct-process[i]->at;
        process[i]->wt=process[i]->tat-process[i]->bt;
    }

}
//(W+S)/S
// float ResponseRatio(Process* p1,int time){
//     int w=time-p1->at;
//     float ratio=(float)(w+p1->at)/p1->at;
//     return ratio;
// }

void HRRN(vector<Process*>&process){
   sort(process.begin(),process.end(),cmp_at);
   priority_queue<Process*,vector<Process*>,Compare>ready;

   int timer=process[0]->at;
   cur_time=timer;
	
   cout<<"GANTT-CHART->"<<endl;
   cout<<"````````"<<endl;
   cout<<"Pid"<<setw(5)<<"S.T"<<setw(5)<<"E.T"<<endl;
   cout<<"---------------"<<endl;
	
   for(int i=0;i<process.size();i++){
   	 if(process[i]->at>timer)break;
   	 ready.push(process[i]);
   }

   while(!ready.empty()){
   	 auto execution=ready.top();
   	 ready.pop();
	 int temp=timer;  
   	 timer+=execution->bt;
   	 execution->rt=0;
   	 execution->ct=timer;
   	 
   	 cur_time=timer;

   	 cout<<execution->pid<<setw(6)<<temp<<setw(6)<<timer<<endl;

   	 while(!ready.empty()){
   	 	ready.pop();
   	 }

   	 for(int l=0;l<process.size();l++){
         if(process[l]->at<=timer){
            if(process[l]->rt>0){
                ready.push(process[l]);
            }
         }else break;
       }
   }

   cout<<endl<<endl;

    generateParams(process);

   int schedule=0;
   int tt=0;
   int wt=0;
   for(auto i:process){
      schedule=max(schedule,i->ct);
      tt+=i->tat;
      wt+=i->wt;
   }
	
   schedule-=process[0]->at;
   int width=5;
   cout<<"Process Attributes->"<<endl;
   cout<<"````````````"<<endl;
   cout<<"Pid"<<setw(width)<<"A.T"<<setw(width)<<"B.T"<<setw(width)<<"C.T"<<setw(7)<<"T.A.T"<<setw(width)<<"W.T"<<endl;
   cout<<setw(width)<<setfill('-')<<"---"<<setw(width)<<"----"<<setw(width)<<"----"<<setw(width)<<"---------------"<<setfill(' ')<<endl;

   for(auto i:process){
    cout<<i->pid<<setw(width+1)<<i->at<<setw(width)<<i->bt<<setw(width+1)<<i->ct<<setw(width+1)<<i->tat<<setw(width)<<i->wt<<endl;
   }
	
   cout<<endl;
   cout<<"AVERAGE T.A.T -> "<<(float)tt/process.size()<<endl;
   cout<<"AVERAGE W.T -> "<<(float)wt/process.size()<<endl;
   cout<<"Scheduling Length -> "<<schedule<<endl;
}

int main(){
    int n;
    cin>>n;
    vector<Process*>process;
    for(int i=0;i<n;i++){
        int pid,at,bt;
        cin>>pid>>at>>bt;
        Process*p1=new Process(pid,at,bt);
        process.push_back(p1);
    }

    HRRN(process);

	return 0;
}
