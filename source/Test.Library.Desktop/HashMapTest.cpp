#include "pch.h"
#include "CppUnitTest.h"
#include "HashMap.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
	TEST_CLASS(TestHashMap)
	{
		HashMap::HashMap<int, int> intMap;
		HashMap::HashMap<int*, int> ptrMap;
		HashMap::HashMap<char*, int> chrMap;
		HashMap::HashMap<std::string, int> strMap;
		HashMap::HashMap<Foo, int> fooMap;
		int x = 1;
		int y = 2;
		int z = 3;
		char* a = "a";
		char* b = "b";
		char* c = "c";
		std::string s = "Steve";
		std::string t = "Tyler";
		std::string u = "Uncle Phil";
		Foo foo, bar, gar;
	public:
		/// Sets up leak detection logic
		static void initializeLeakDetection()
		{
#if _Debug
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif //_Debug
		}

		/// Detects if memory state has been corrupted
		static void finalizeLeakDetection()
		{
#if _Debug
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif //_Debug
		}

		TEST_METHOD_INITIALIZE(methodInitialize)
		{
			initializeLeakDetection();
			intMap.clear();
			ptrMap.clear();
			chrMap.clear();
			strMap.clear();
			fooMap.clear();
			x = 1;
			y = 2;
			z = 3;
			a = "a";
			b = "b";
			c = "c";
			s = "Steve";
			t = "Tyler";
			u = "Uncle Phil";
			foo = Foo(1);
			bar = Foo(2);
			gar = Foo(3);
		}

		TEST_METHOD_CLEANUP(methodCleanup)
		{
			finalizeLeakDetection();
		}

		TEST_METHOD(TestTemplateSpecialization)
		{
			// int tests
			intMap.insert(std::pair<int, int>(1, 1));
			Assert::IsTrue(intMap.containsKey(1), L"intMap does not contain inserted key");


			// ptr tests
			ptrMap.insert(std::pair<int*, int>(&x, 1));
			Assert::IsTrue(ptrMap.containsKey(&x), L"ptrMap does not contain inserted key");


			// chr tests
			chrMap.insert(std::pair<char*, int>(c, 1));
			Assert::IsTrue(chrMap.containsKey(c), L"charMap does not contain inserted key");


			// str tests
			strMap.insert(std::pair<std::string, int>(s, 1));
			Assert::IsTrue(strMap.containsKey(s), L"stringMap does not contain inserted key");


			// foo tests
			fooMap.insert(std::pair<Foo, int>(foo, 1));
			Assert::IsTrue(fooMap.containsKey(foo), L"fooMap does not contain inserted key");
		}

		TEST_METHOD(TestCopyConstructor)
		{
			// int tests
			HashMap::HashMap<int, int> intcopy1(intMap);
			Assert::IsTrue(intMap.size() == intcopy1.size(), L"HashMap sizes not equal");

			intMap.insert(std::pair<int, int>(1, 1));
			HashMap::HashMap<int, int> intcopy2(intMap);
			Assert::AreEqual(intMap.size(), intcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(intMap.begin() == intMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(intcopy2.begin() == intcopy2.end(), L"Begin of non-empty HashMap equals end");

			// ptr tests
			HashMap::HashMap<int*, int> ptrcopy1(ptrMap);
			Assert::IsTrue(ptrMap.size() == ptrcopy1.size(), L"HashMap sizes not equal");

			ptrMap.insert(std::pair<int*, int>(&x, 1));
			HashMap::HashMap<int*, int> ptrcopy2(ptrMap);
			Assert::AreEqual(ptrMap.size(), ptrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(ptrMap.begin() == ptrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(ptrcopy2.begin() == ptrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// chr tests
			HashMap::HashMap<char*, int> chrcopy1(chrMap);
			Assert::IsTrue(chrMap.size() == chrcopy1.size(), L"HashMap sizes not equal");

			chrMap.insert(std::pair<char*, int>(a, 1));
			HashMap::HashMap<char*, int> chrcopy2(chrMap);
			Assert::AreEqual(chrMap.size(), chrcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(chrMap.begin() == chrMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(chrcopy2.begin() == chrcopy2.end(), L"Begin of non-empty HashMap equals end");


			// str test
			HashMap::HashMap<std::string, int> strcopy1(strMap);
			Assert::IsTrue(strMap.size() == strcopy1.size(), L"HashMap sizes not equal");

			strMap.insert(std::pair<std::string, int>(s, 1));
			HashMap::HashMap<std::string, int> strcopy2(strMap);
			Assert::AreEqual(strMap.size(), strcopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(strMap.begin() == strMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(strcopy2.begin() == strcopy2.end(), L"Begin of non-empty HashMap equals end");
			
			
			// foo tests
			HashMap::HashMap<Foo, int> foocopy1(fooMap);
			Assert::IsTrue(fooMap.size() == foocopy1.size(), L"HashMap sizes not equal");

			fooMap.insert(std::pair<Foo, int>(foo, 1));
			HashMap::HashMap<Foo, int> foocopy2(fooMap);
			Assert::AreEqual(fooMap.size(), foocopy2.size(), L"HashMap sizes not equal");
			Assert::IsFalse(fooMap.begin() == fooMap.end(), L"Begin of non-empty HashMap equals end");
			Assert::IsFalse(foocopy2.begin() == foocopy2.end(), L"Begin of non-empty HashMap equals end");
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			// int tests
			// ptr tests
			// chr tests
			// str tests
			// foo tests
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestFind)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestInsert)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestRemove)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIndexOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestBegin)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestEnd)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestClear)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestSize)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestContainsKey)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorCopyConstructor)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorAssignmentOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorIncrementOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorDereferenceOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorArrowOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorEqualityOperator)
		{
			Assert::Fail(L"Method not implemented");
		}

		TEST_METHOD(TestIteratorNotEqualOperator)
		{
			Assert::Fail(L"Method not implemented");
		}
	};
}
