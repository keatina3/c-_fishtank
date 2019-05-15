#ifndef _SITE_H_
#define _SITE_H_

// vector of Fish pointers //
typedef std::vector<Fish*> Fish_vec;

class Site {
private:
    std::vector<Fish_vec> fish;     // stores all fish on Site in 3 vectors //

public:
    Site();
    ~Site();

    Fish *get_fish(const int fish_id, const int index) const;
    void add_fish(Fish *fish);
    void del_fish(const int fish_id, const int index, const bool kill);
    int get_count(const int fish_id) const;
    int count_fed(const int fish_id) const;
    void feed_fish(const int fish_id);
    int kill_fish(const int fish_id);
};

#endif
