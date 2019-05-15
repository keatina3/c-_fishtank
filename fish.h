#ifndef _FISH_H_
#define _FISH_H_

class Fish {
protected:
    int moves; 
    bool hungry;
    int fish_id;

public:
    Fish();
    virtual ~Fish(){};

    int get_id() const;
    int get_moves() const;
    bool is_hungry() const;
    void feed();
    virtual void move(const int *src, int *coords)=0;
};

class Minnow : public Fish {
public:
    Minnow();
    ~Minnow(){};

    void move(const int *src, int *coords);
};

class Tuna : public Fish {
public:
    Tuna();
    ~Tuna(){};

    void move(const int *src, int *coords);
};

class Shark : public Fish {
public:
    Shark();
    ~Shark(){};

    void move(const int *src, int *coords);
};

#endif
