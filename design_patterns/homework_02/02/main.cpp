#include <iostream>
#include <unordered_map>
#include <string>


class IDatabase
{
    public:

        virtual ~IDatabase() = default;

        virtual std::string get_data(const std::string& key) const = 0;
};

class Database : public IDatabase
{
    public:

        std::string get_data(const std::string& key) const override
        {
            return "Very Big Data String: " + key;
        }
};

class MockDatabase : public IDatabase
{
    public:

        std::string get_data(const std::string& key) const override
        {
            return "Mock data";
        }
};

class DatabaseProxy : public IDatabase
{
    protected:

        IDatabase& database_;

    public:

        DatabaseProxy(const DatabaseProxy&) = delete;
        DatabaseProxy& operator=(const DatabaseProxy&) = delete;

        virtual ~DatabaseProxy() = default;

        explicit DatabaseProxy (IDatabase& db) : database_(db)
        {
        }
};

class CacheProxy : public DatabaseProxy
{
    private:
    
        mutable std::unordered_map<std::string, std::string> cache_;

    public:

        explicit CacheProxy (IDatabase& db) : DatabaseProxy(db)
        {
        }

        std::string get_data(const std::string& key) const override
        {
            auto it = cache_.find(key);

            if (it == cache_.end())
            {
                std::cout << "Get from database: ";

                it = cache_.emplace(key, database_.get_data(key)).first;
            }
            else
            {
                std::cout << "Get from cache: ";
            }

            return it->second;
        }
};

class LimitedAccessProxy : public DatabaseProxy
{
    private:

        mutable std::size_t shots_;

    public:

        explicit LimitedAccessProxy (IDatabase& db, size_t shots) : DatabaseProxy(db), shots_(shots)
        {
        }

        std::string get_data(const std::string& key) const override
        {
            if (shots_ > 0)
            {
                --shots_;
                return database_.get_data(key);
            }
            else
            {
                return "The limit has been reached.";
            }
        }
};


int main()
{
    using std::cout;

    Database db;
    CacheProxy cache(db);
    LimitedAccessProxy  limit(cache, 4);

    cout << "limit + cache test:\n";

    for (int i = 0; i < 5; ++i)
    {
        cout << limit.get_data("key") << '\n';
    }

    cout << "cache + limit test:\n";

    LimitedAccessProxy limit_b(db, 4);
    CacheProxy cache_b(limit_b);

    for (int i = 0; i < 5; ++i)
    {
        cout << cache_b.get_data("key") << '\n';
    }

    cout << "mock database + limit + cache test:\n";
    
    MockDatabase mock;
    CacheProxy cache_c(mock);
    LimitedAccessProxy limit_c(cache_c, 4);

    for (int i = 0; i < 5; ++i)
    {
        cout << limit_c.get_data("key") << '\n';
    }

    return 0;
}