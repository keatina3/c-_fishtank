#ifndef _TANK_H_
#define _TANK_H_

class Tank {
private:
    Site tank[5][5][5];     // change to dynamic when program working //
    int tot_count[3];
    int fish_count[3][5][5][5];      // 0 = minnows, 1 = tuna, 2 = sharks //

public:
    Tank();
    Tank(const int minnows, const int tuna, const int sharks);
    ~Tank(){};
    
    //int get_count(const int fish_id) const;
    void sweep();
    bool fish_present(const int *site, const int fish_id) const;
    void move(const int *site, const int fish_id);

    int check_outcomes(const int *site);

    void minnow_breed(const int *site);
    void tuna_breed(const int *site);
    void shark_breed(const int *site);
    void tuna_feed(const int *site);
    void shark_feed(const int *site);
    void feeding_frenzy(const int *site);
};

#endif
