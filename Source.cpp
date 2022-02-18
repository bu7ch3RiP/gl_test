#include <iostream>
#include <filesystem>
#include <string>
#include <Windows.h>
#include "Searcher.h"
#include <mutex>
#include <thread>
#include <chrono>
#include <future>

namespace fs = std::filesystem;

Searcher search;
std::mutex mtx;
const int max_amount_of_treads = 8;
int counterr = 0;
std::atomic<uint_fast32_t> counter = 0;

void thread_work(std::queue<std::string>& tv, std::string& filename)
{
	mtx.lock();
	
	fs::path tp = tv.front();

	if (tv.empty() == 0) {
		tv.pop();
	}

	mtx.unlock();

	if (fs::is_regular_file(tp) == 0)
	{
		if (search.finder(tp, filename) == 1)
		{
			search.set_found(true);
		}
	}
	--counter;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string filename = "56kl.txt";
	/*std::cout << "Enter file name: ";
	std::cin >> filename;*/
	
	/*search.finder("E:\\", filename);
	std::cout << search.get_current_dir();*/
	
	search.set_list_of_root_dir();
	std::queue<std::string> v = search.get_list_of_root_dir();
	

	while ((search.get_found() != true) || (v.empty() == 0))
	{
		if (counter >= max_amount_of_treads)
			continue;
		if ((search.get_found() == true) || (v.empty() == 1))
		{
			std::cout << search.get_current_dir() << std::endl;
			break;
		}
		std::promise<void> p;
		std::future<void> f3 = p.get_future();
		std::thread(thread_work, std::ref(v), std::ref(filename)).detach();
		++counter;
	}

	while (true && (0 == counter));
	  std::this_thread::sleep_for(std::chrono::seconds(1));

	return 0;
}