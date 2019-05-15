#ifndef _TANK_H_
#define _TANK_H_

class Tank {
private:
    Site tank[5][5][5];     // change to dynamic when program working //
    int tot_count[3];

public:
    Tank();
    Tank(const int minnows, const int tuna, const int sharks);
    ~Tank(){};
   
    const Site* get_site(const int *site) const; 
    int get_count(const int fish_id) const;
    bool fish_present(const int *site, const int fish_id) const;
    void print() const;
    
    void sweep();
    void move(const int *site, int *dest, const int fish_id);
    int check_outcomes(const int *site, void (Tank::**outcome_fns)(const int *));
    
    void minnow_breed(const int *site);
    void tuna_breed(const int *site);
    void shark_breed(const int *site);
    void tuna_feed(const int *site);
    void shark_feed(const int *site);
    void feeding_frenzy(const int *site);
};

std::ostream &operator<<(std::ostream &os, const Tank &tank);

#endif
