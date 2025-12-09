class Player : public GameObject {
private:
    int health;                    // Жизни (1-3)
    float move_speed;              // Скорость движения

public:
    Player(float x, float y);

    void update() override;        // Пока пусто
    void draw() override;          // Пока пусто

    int getHealth() const;
    void loseHealth();
    void gainHealth();
    bool isAlive() const;
};