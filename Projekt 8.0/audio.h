
#ifndef PROJEKT_CPP_AUDIO_H
#define PROJEKT_CPP_AUDIO_H



class Audio
{
public:
    sf::Music music;

    // Szieki muzyki
    std::string current_music = ""; // Aktualna muzyka
    std::string grimm_music = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/grimm_music.wav";
    std::string amusement_park = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/amusement_park.wav";
    std::string monster_music = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/monster_music.wav";
    std::string hollow_music = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/hollow_music.wav";
    std::string sifnificance = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/Significance.wav";

    // Sciezki dzwiekow
    std::string sword_attack = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/sword_attack.wav";
    std::string explosion = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/creeper_sound.wav";
    std::string crystal_attack = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/crystal_attack.wav";
    std::string hit_sound = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/hit_sound.wav";
    std::string fire_attack = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/fire_attack.wav";
    std::string laser_attack = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/laser_attack.wav";
    std::string dash_sound = "/Users/mcwilan/Library/Mobile Documents/com~apple~CloudDocs/pro3/Projekt cpp/Music/dash_sound.wav";

    // Buffery
    sf::SoundBuffer swordAttack;
    sf::SoundBuffer crystalAttack;
    sf::SoundBuffer explosionAttack;
    sf::SoundBuffer hitSound;
    sf::SoundBuffer fireAttack;
    sf::SoundBuffer laserAttack;
    sf::SoundBuffer dashSound;

    // Dzwieki
    sf::Sound SwordAttack;
    sf::Sound ExplosionAttack;
    sf::Sound CrystalAttack;
    sf::Sound HitSound;
    sf::Sound FireAttack;
    sf::Sound LaserAttack;
    sf::Sound DashSound;


    void music_play(std::string music_dir)
    {
        if(music_dir != current_music)
        {
            if(music.openFromFile(music_dir))
            {
                music.play();
                current_music = music_dir;
            }
        }
    }

    Audio()
    {
        // Buffery
        swordAttack.loadFromFile(sword_attack);
        crystalAttack.loadFromFile(crystal_attack);
        explosionAttack.loadFromFile(explosion);
        hitSound.loadFromFile(hit_sound);
        fireAttack.loadFromFile(fire_attack);
        laserAttack.loadFromFile(laser_attack);
        dashSound.loadFromFile(dash_sound);

        // Dzwieki
        SwordAttack.setBuffer(swordAttack);
        CrystalAttack.setBuffer(crystalAttack);
        ExplosionAttack.setBuffer(explosionAttack);
        HitSound.setBuffer(hitSound);
        FireAttack.setBuffer(fireAttack);
        LaserAttack.setBuffer(laserAttack);
        DashSound.setBuffer(dashSound);

        // Glosnosc dzwiekow
        SwordAttack.setVolume(10);
        CrystalAttack.setVolume(10);
        ExplosionAttack.setVolume(10);
        HitSound.setVolume(10);
        FireAttack.setVolume(30);
        LaserAttack.setVolume(30);
        DashSound.setVolume(50);

        music.setVolume(20);
        music.setLoop(true); // Odtwarzaj w petli
    }




};

#endif //PROJEKT_CPP_AUDIO_H
