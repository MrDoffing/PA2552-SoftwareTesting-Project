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
			server->clear(); // remove all files
			delete server;
			server = nullptr;
		}
		TEST_METHOD(TestMethod_createUser)
		{
			Logger::WriteMessage("InMethod - Create User");

			// create user
			UserID id = "UserTest";
			Assert::IsTrue(server->createUser(id));
			// fetch user
			User user;
			Assert::IsTrue(server->fetchUser(id, user));
			// validate user properties
			Assert::IsTrue(user.getUsername() == id); // same username
			Assert::IsTrue(user.getBankValue() == 0); // no currency
			Assert::IsTrue(user.getInventory().size() == 0); // no items
		}
		TEST_METHOD(TestMethod_createItemForUser)
		{
			Logger::WriteMessage("InMethod - create item for user");

			// create user
			UserID id = "UserTest";
			Assert::IsTrue(server->createUser(id));
			// validate before creating item
			User user_before;
			Assert::IsTrue(server->fetchUser(id, user_before));
			Assert::IsTrue(user_before.getInventory().size() == 0); // empty at start

			// create item and give to user
			Item item("item0", 5, "desc0");
			server->createItemForUser(id, item);

			// validate new item
			User user_after;
			Assert::IsTrue(server->fetchUser(id, user_after));
			Assert::IsTrue(user_after.getInventory().size() == 1); // correct size
			Assert::IsTrue(user_after.getInventory()[0] == item); // the same item

		}
		TEST_METHOD(TestMethod_storage) 
		{
			Logger::WriteMessage("InMethod - Read and Write Storage");

			// create item for storage
			Item item("item0", 10, "description");
			Assert::IsTrue(server->createItemForStorage(item));
			// fetch storage
			Inventory inv;
			Assert::IsTrue(server->fetchStorage(inv));
			// validate storage
			Assert::IsTrue(inv.size() == 1);
			Assert::IsTrue(inv[0] == item);
		}
		TEST_METHOD(TestMethod_fetchItems)
		{
			Logger::WriteMessage("InMethod - Fetch Storage");

			Item item0("item0", 10, "description0");
			Item item1("item1", 5, "description1");
			// fill expected inventory
			Inventory inv_expected;
			inv_expected.push(item0);
			inv_expected.push(item1),
			// insert items in storage
			Assert::IsTrue(server->createItemForStorage(item0));
			Assert::IsTrue(server->createItemForStorage(item1));
			// read storage
			Inventory inv_storage;
			Assert::IsTrue(server->fetchStorage(inv_storage));
			// validate storage
			Assert::IsTrue(inv_storage == inv_expected);
		}

		TEST_METHOD(TestMethod_buy)
		{
			Logger::WriteMessage("InMethod - Buy");

			// create user
			UserID uid = "TestUser";
			Assert::IsTrue(server->createUser(uid, 20));
			// create item in storage
			ItemID iid = "item0";
			Item item(iid, 10, "description");
			Assert::IsTrue(server->createItemForStorage(item));
			// validate
			User user;
			Assert::IsTrue(server->fetchUser(uid, user));
			Assert::IsTrue(user.getInventory().size() == 0);
			Assert::IsTrue(user.getBankValue() == 20);
			Inventory inv;
			Assert::IsTrue(server->fetchStorage(inv));
			Assert::IsTrue(inv.size() == 1);

			// buy item
			server->buy(uid, iid);
			
			// validate
			Assert::IsTrue(server->fetchUser(uid, user));
			Assert::IsTrue(user.getInventory().size() == 1);
			Assert::IsTrue(user.getBankValue() == 10);
			Assert::IsTrue(user.getInventory()[0] == item);

			Assert::IsTrue(server->fetchStorage(inv));
			Assert::IsTrue(inv.size() == 0);
		}
		TEST_METHOD(TestMethod_sell)
		{
			Logger::WriteMessage("InMethod - Sell");

			// create user
			UserID uid = "UserTest";
			Assert::IsTrue(server->createUser(uid));
			// create item for user
			ItemID iid = "item0";
			Item item(iid, 10, "description");
			server->createItemForUser(uid, item);
			// validate
			User user;
			Inventory inv;
			Assert::IsTrue(server->fetchUser(uid, user));
			Assert::IsTrue(user.getInventory().size() == 1); // correct nr of items
			Assert::IsTrue(user.getBankValue() == 0); // correct currency

			Assert::IsTrue(server->fetchStorage(inv));
			Assert::IsTrue(inv.size() == 0); // no items in storage

			// sell item
			server->sell(uid, iid);

			// validate
			Assert::IsTrue(server->fetchUser(uid, user));
			Assert::IsTrue(user.getInventory().size() == 0); // no items in inventory
			Assert::IsTrue(user.getBankValue() == 10); // received cash

			Assert::IsTrue(server->fetchStorage(inv));
			Assert::IsTrue(inv.size() == 1); // received item
			Assert::IsTrue(inv[0] == item); // is the correct item
		}
	};
}
