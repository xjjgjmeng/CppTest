#include <memory>

void reset()
{
	/*
		1. Saves a copy of the current pointer
		2. Overwrites the current pointer with the argument
		3. If the old pointer was non-empty, deletes the previously managed object
	*/
	auto p = std::make_unique<int>();
	// p.reset(p.get()); // 将导致崩溃
	p.reset(p.release()); // ok
}

void release()
{
	auto p = std::make_unique<int>();
	p.reset(); // 执行后，自己为empty，删除被管理对象
	p.release(); // 执行后，自己为empty，不删除被管理对象
}

void close_file(std::FILE* fp) { std::fclose(fp); }

int main()
{
	// 管理数组
	{
		std::unique_ptr<int[]> p1(new int[3]);
		auto p2 = std::make_unique<int[]>(3);
	}

	// 使用unique_ptr关闭C语言的FILE
	{
		{
			struct FileCloser
			{
				void operator()(std::FILE* fp) const
				{
					std::fclose(fp);
				}
			};
			std::unique_ptr<std::FILE, FileCloser> fp(std::fopen("my.ini", "r"));
		}

		{
			std::unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("my.ini", "r"), &close_file);
		}
	}

	reset();
	release();

	return 0;
}