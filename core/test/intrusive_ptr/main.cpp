#include <vector>
#include <cstddef>

#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>
#include <cassert>
#include <iostream>

using namespace actor_zeta;

template<class T, class... Ts>
intrusive_ptr<T> make_counted(Ts &&... xs) {
    return intrusive_ptr<T>(new T(std::forward<Ts>(xs)...), false);
}

int class0_instances = 0;
int class1_instances = 0;

class class0;

class class1;

using class0ptr = intrusive_ptr<class0>;
using class1ptr = intrusive_ptr<class1>;

class class0 : public ref_counted {
public:
    explicit class0(bool subtype = false) : subtype_(subtype) {
        if (!subtype) {
            ++class0_instances;
        }
    }

    virtual ~class0() {
        if (!subtype_) {
            --class0_instances;
        }
    }

    bool is_subtype() const {
        return subtype_;
    }

    virtual class0ptr create() const {
        return make_counted<class0>();
    }

private:
    bool subtype_;
};

class class1 : public class0 {
public:
    class1() : class0(true) {
        ++class1_instances;
    }

    ~class1() override {
        --class1_instances;
    }

    class0ptr create() const override {
        return make_counted<class1>();
    }
};

class0ptr get_test_rc() {
    return make_counted<class0>();
}

class0ptr get_test_ptr() {
    return get_test_rc();
}

struct fixture {
    ~fixture() {
        assert(class0_instances == 0);
        assert(class1_instances == 0);
    }
};


int main() {

    /// make_counted

    {
        auto p = make_counted<class0>();
        assert(class0_instances == 1);
        assert(p->unique() == true);
    }

    /// reset
    {
        class0ptr p0;
        p0.reset(new class0, false);
        assert(class0_instances == 1);
        assert(bool(p0->unique()) == true);
    }

    /// get_test_rc
    {
        class0ptr p1;
        p1 = get_test_rc();
        class0ptr p2 = p1;
        assert(class0_instances == 1);
        assert(p1->unique() == false);
    }

    /// list
    {
        std::vector<class0ptr> pl;
        pl.push_back(get_test_ptr());
        pl.push_back(get_test_rc());
        pl.push_back(pl.front()->create());
        assert(pl.front()->unique());
        assert(class0_instances == 3);
    }

    /// full_test
    {
        auto p1 = make_counted<class0>();
        assert(p1->is_subtype() == false);
        assert(p1->unique() == true);
        assert(class0_instances == 1);
        assert(class1_instances == 0);
        p1.reset(new class1, false);
        assert(p1->is_subtype() == true);
        assert(p1->unique() == true);
        assert(class0_instances == 0);
        assert(class1_instances == 1);
        auto p2 = make_counted<class1>();
        p1 = p2;
        assert(p1->unique() == false);
        assert(class0_instances == 0);
        assert(class1_instances == 1);
        assert(p1 == static_cast<class0 *>(p2.get()));
    }

    return 0;
}