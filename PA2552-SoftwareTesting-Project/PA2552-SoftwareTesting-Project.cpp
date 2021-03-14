#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Server.h"

namespace PA2552SoftwareTestingProject
{
	TEST_CLASS(ClassServer)
	{
	private:
		const string test_path = "./TESTING/";
		Server* server = nullptr;
	public:
		
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup");
		}

		TEST_METHOD_INITIALIZE(MethodInitialize)
		{
			Logger::WriteMessage("In Method Initialize");
			server = new Server(test_path);
		}
		TEST_METHOD_CLEANUP(MethodCleanup)
		{
			Logger::WriteMessage("In Method Cleanup");
			server->clear();
			delete server;
			server = nullptr;
		}
		TEST_METHOD(TestMethod_createUser)
		{
			Logger::WriteMessage("InMethod - Create User");
			UserID id = "UserTest";
			bool check_create = server->createUser(id);
			Assert::IsTrue(check_create);
			User user;
			bool check_fetch = server->fetchUser(id, user);
			Assert::IsTrue(check_fetch);
			Assert::IsTrue(user.getUsername() == id); // same username
			Assert::IsTrue(user.getBankValue() == 0); // no currency
			Assert::IsTrue(user.getInventory().size() == 0); // no items
		}
		TEST_METHOD(TestMethod_storage) 
		{
			Logger::WriteMessage("InMethod - Read and Write Storage");
			Inventory inv;
			inv.push(Item("item0", 10, "description"));
			bool check_write = server->writeStorage(inv);
			Assert::IsTrue(check_write);
			bool check_read = server->fetchStorage(inv);
			Assert::IsTrue(check_read);

			Assert::IsTrue(inv.size() == 1);
		}
		TEST_METHOD(TestMethod_fetchItems)
		{
			Logger::WriteMessage("InMethod - Fetch Storage");
			Inventory inv_write;
			inv_write.push(Item("item0", 10, "description0"));
			inv_write.push(Item("item1", 5, "description1"));
			bool check_write = server->writeStorage(inv_write);
			Assert::IsTrue(check_write);
			Inventory inv_read;
			bool check_read = server->fetchStorage(inv_read);
			Assert::IsTrue(check_read);

			Assert::IsTrue(inv_read == inv_write);
		}

		TEST_METHOD(TestMethod_buy)
		{
			Logger::WriteMessage("InMethod - Buy");
			// create user
			User user("user0", 20);
			server->writeUser(user);
			// create item in storage
			Inventory inv;
			Item item("item0", 10, "description");
			inv.push(item);
			server->writeStorage(inv);
			// validate
			Assert::IsTrue(server->fetchUser("user0", user));
			Assert::IsTrue(user.getInventory().size() == 0);
			Assert::IsTrue(user.getBankValue() == 20);

			Assert::IsTrue(server->fetchStorage(inv));
			Assert::IsTrue(inv.size() == 1);

			// buy item
			server->buy("user0", "item0");
			
			// validate
			Assert::IsTrue(server->fetchUser("user0", user));
			Assert::IsTrue(user.getInventory().size() == 1);
			Assert::IsTrue(user.getBankValue() == 10);
			Assert::IsTrue(user.getInventory()[0] == item);

			Assert::IsTrue(server->fetchStorage(inv));
			Assert::IsTrue(inv.size() == 0);
			Assert::Fail();
		}
		TEST_METHOD(TestMethod_sell)
		{
			Logger::WriteMessage("InMethod - Sell");
			// create user
			User user("user0", 0);
			Item item("item0", 10, "description");
			user.getInventory().push(item);
			server->writeUser(user);
			// validate
			Inventory inv;
			Assert::IsTrue(server->fetchUser("user0", user));
			Assert::IsTrue(user.getInventory().size() == 1);
			Assert::IsTrue(user.getBankValue() == 0);

			Assert::IsTrue(server->fetchStorage(inv));
			Assert::IsTrue(inv.size() == 0);

			// sell item
			server->sell("user0", "item0");

			// validate
			Assert::IsTrue(server->fetchUser("user0", user));
			Assert::IsTrue(user.getInventory().size() == 0);
			Assert::IsTrue(user.getBankValue() == 10);

			Assert::IsTrue(server->fetchStorage(inv));
			Assert::IsTrue(inv.size() == 1);
			Assert::IsTrue(inv[0] == item);
		}
	};
}
