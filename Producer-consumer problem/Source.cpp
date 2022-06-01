#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <thread>
#include <ctime>
#include <mutex>
#include <condition_Variable>
#include <queue>
#include <functional>


using namespace std;

float BaseTemperature = 35;
bool bCanRun = true;


void Delay(int time)
{
	clock_t now = clock();

	while (clock() - now < time);
}

void Timer()
{
	Delay(30 * 1000);

	bCanRun = false;
}

class monitor 
{
private:
	enum {EMPTY,WAIT,HEALING} ConsumerState[8]; //8位客人狀態
	enum { NOTHING , WORKING} DoctorState[3];  //3位醫生狀態
	condition_variable Consumer[8];			//讓8個個人有各自的條件變數去鎖住執行緒的進行
	queue<int> WaitRoom;			//等候室,內部座位後面會設定為3個位子
	
public:
	//给8個執行緒狀態使外部空間呼叫時不會呼叫到正在使用的執行緒,而產程錯誤
	bool ThreadState[8] = { false ,false,false,false,false,false,false,false };
	//初始化
	monitor() { 

		for (int i = 0; i < 3; i++)
			DoctorState[i] = NOTHING;
		for (int i = 0; i < 8; i++)
			ConsumerState[i] = EMPTY;
		WaitRoom = queue<int>();
	}

	void VisitIn(int i);		//進入診所對客人檢查
	void Test(int i);			//檢查診所內部狀態
	void VistOut(int i,int j);	//看完診離開

	


};


int main() {
	//斷開C++跟C之間的輸出保護裝置,提高cout速度
	std::ios::sync_with_stdio(false);        

	srand(time(0));
	monitor ConsumerProble;
	thread *Consumer = new thread[8];	//產生8個執行緒對應8個客人
	thread TTimer(Timer);				//產生一個執行緒處理時間
	int RandNumber;

	
	while (bCanRun)		//Timer的30秒跑完會改為false跳出迴圈
	{
		RandNumber = rand() % 8;	//亂數產生0~7
		
		//確認該客人是否正在診所內,true表正在診所內,false表可以去看診
		if (ConsumerProble.ThreadState[RandNumber] == false)
		{
			//使用std::bind function解決類中成員函數的多執行續呼叫,又或者使用Lambda處理此問題
			Consumer[RandNumber]= thread(std::bind(&monitor::VisitIn,&ConsumerProble, RandNumber));
			//使用detach讓主程式不去等待執行緒, 如使用join會使主程式必須等待執行緒完成才能繼續
			Consumer[RandNumber].detach();

			Delay((rand() % 3+ 0.1) * 1000); //至少0.1到3.1秒,拉長減少發生執行太快產生兩個執行緒同時看同個醫生問題
											 //不然可能2次以上的0秒可能會使得狀態還未更新進而產生兩位客人同時看同一位醫生的問題
		}

	}

	delete[] Consumer;
	TTimer.join(); //主程式需等待Timer跑完才能繼續往下跑


	cout << "Stop" << endl;


	return 0;
}



void monitor::VisitIn(int i)
{
	ThreadState[i] = true;	//將執行緒狀態改變
	srand(time(0));

	float Temperature = BaseTemperature + (rand() % 5) + ((float)(rand() % 5) / 10);

	//檢測是否發燒
	if (Temperature >= 37.5)
	{
		cout << "Consumer " << i << " : 發燒被請出診所 \n";
		ThreadState[i] = false;
		return;
	}
				
	else
	{
		 //未發燒先進入Test內做判斷
		Test(i);
		//如果離開Test後ConsumerState為WAIT表示客人正在等候室等候
		if (ConsumerState[i] == WAIT)
		{
			//因等候所以把執行緒鎖住
			mutex Mutex;
			unique_lock<mutex> Lock(Mutex);
			//執行緒停在130行等待解鎖
			Consumer[i].wait(Lock);
			//呼叫解鎖後才執行132行
			Test(i);
		}
		//結束回復執行緒狀態
		ThreadState[i] = false;
		return;
	}
}

	


void monitor::Test(int i)
{
	//先檢查3未醫師是否沒看診
	for (int j = 0; j < 3; j++)
	{
		//沒看診就進入看診並調整內部狀態
		if (DoctorState[j] == NOTHING)
		{
			DoctorState[j] = WORKING;

			if(ConsumerState[i] == EMPTY)
				cout << "Consumer " << i << " : 進入診療室讓Doctor" << (char)(j + 65) << "診療中 \n";
			else if(ConsumerState[i] == WAIT)
				cout << "Consumer " << i << " : 從候診椅進入診療室讓Doctor" << (char)(j + 65) << "診療中 \n";

			ConsumerState[i] = HEALING;
			//模擬看診的時間
			Delay(((rand() % 6) +2 )* 1000);   //至少執行2秒到8秒,拉長時間減少多執行緒之間的搶先問題
			//Consumer[i].notify_one();      //喚醒consumer第i個鎖

			VistOut(i, j);//結束後進入此函數

			return;
		}

	}
	//下方為所有醫生再忙執行
	if (ConsumerState[i] == EMPTY)
	{
		//如果等候室人數小於3就進入等候
		if (WaitRoom.size() < 3)
		{
			ConsumerState[i] = WAIT;
			WaitRoom.push(i);	
			cout << "Consumer " << i << " : 候診椅等候 \n";
			return;
		}
		//否則直接離開診所
		else
		{
			cout << "Consumer " << i << " : 沒位置離開了\n";
			return;
		}

	}

}

//看完診要離開的設定
void monitor::VistOut(int i, int j)
{

	cout << "Consumer " << i << " : 看完離開診所\n";

	//回復狀態
	ConsumerState[i] = EMPTY;
	DoctorState[j] = NOTHING;
	//確認等候室是否有人等待,優先給等候室的人執行,模擬排隊
	if (!WaitRoom.empty())
	{	
		int temp = WaitRoom.front();
		WaitRoom.pop();
		Consumer[temp].notify_one();      //喚醒consumer i 的鎖,表示喚醒排隊等待的執行緒
		//Test(temp);
	}

	

	return;
}




