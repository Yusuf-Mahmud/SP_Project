#include "GameScenes.h"

float TextTimer = 0.085, TextDelay = 0.085, ChatTime = 2, ChatDelay = 2, s0ChatTime = 4, s0ChatDelay = 4;
enemies FinalBossTalk;
rects HeroTalk;

bool tch = 1;
void DisplayText(Text &t, string &s, int &idx, enemies& e, rects& h, string talker)
{
	if (TextTimer < 0)
	{
		if (tch)
		{
			t.setString(t.getString() + s[idx]);
			if (t.findCharacterPos(idx).x > window.getSize().x - 128 && s[idx] == ' ')
				t.setString(t.getString() + '\n');
		}
		if (idx + 2 < s.size() && s[idx + 1] == '.' && s[idx + 2] == '.')
		{
			tch = 0;
			if (s0ChatTime > 0)
			{
				s0ChatTime -= DeltaTime;
				window.draw(t);
			}
			else
			{
				tch = 1;
				s0ChatTime = s0ChatDelay;
				t.setString("");
				idx += 3;
			}
		}
		else if (s[idx] == ',')
			TextTimer = TextDelay + 0.5, idx++;
		else if (idx + 1 < s.size() && s[idx + 1] != ' ')
			TextTimer = TextDelay, idx++;
		else
			idx++;
	}
	else
	{
		TextTimer -= DeltaTime;
	}
	if (talker == "no")
	{
		window.draw(t);
	}
	else
	{
		window.draw(e.sprite);
		window.draw(h.rect);
		if (talker == "hero")
			window.draw(HeroTalk.rect);
		else
			window.draw(FinalBossTalk.sprite);
		window.draw(t);
	}
}

Font f;
Text t0;
string s0;
void GameScenes::Scene0Set()
{
	f.loadFromFile("./res/Fonts/Vogue.ttf");
	s0 = "It all starts win i was traveling with the only person i know and trust in the whole world, every person we meet ";
	s0 += "thinks we are brothers, however we are not, but i loved him as my real brother..";
	s0 += "We were descovering the surroundings of our village until we fell in a monsters trap and i ran away whith all my strength";
	s0 += " I thought my brother will catch up with me and waited far away, but he did not come, I lost my best friend then..";
	s0 += "i will avenge him at any cost, i will kill all those creepe monsters and relieve people from their evil";
	t0.setFont(f);
	t0.setString("");
	t0.setFillColor(Color::White);
	t0.setPosition(32, window.getSize().y / 2 - 64);
}

int i0 = 0;
RectangleShape screen;
void GameScenes::scene0(enemies &e, rects &h)
{
	screen.setSize({ (float)window.getSize().x, (float)window.getSize().y });
	screen.setFillColor(Color::Black);
	if (i0 < s0.size())
	{
		DisplayText(t0, s0, i0, e, h, "no");
	}
	else if (ChatTime > 0 && i0 == s0.size())
	{
		ChatTime -= DeltaTime;
		window.draw(e.sprite);
		window.draw(h.rect);
		window.draw(HeroTalk.rect);
		window.draw(screen);
		window.draw(t0);
	}
	else
	{
		ChatTime = ChatDelay;
		i0++;
		scene0ch = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		ChatTime = ChatDelay;
		i0++;
		scene0ch = 0;
	}
}

Text t1;
string s1;
void GameScenes::Scene1Set(enemies &e, rects &h)
{
	FinalBossTalk.set(86, window.getSize().y - 128, 0, "FinalBoss", "NoShadow", "NoShield");
	FinalBossTalk.sprite.setOrigin(32, 32);
	FinalBossTalk.sprite.setScale(4, 4);
	HeroTalk.size = { 50, 50 };
	HeroTalk.set();
	HeroTalk.rect.setScale(4, 4);
	HeroTalk.rect.setPosition(86, window.getSize().y - 128);
	e.sprite.setOrigin(32, 32);
	e.sprite.setPosition(window.getSize().x * 3 / 4, window.getSize().y / 2);
	e.sprite.setTextureRect(IntRect(0, 64 * 9, 64, 64));
	h.rect.setOrigin(25, 25);
	h.rect.setPosition((float)window.getSize().x / 4, (float)window.getSize().y / 2);
	s1 = "Ah, He is so strong";
	t1.setFont(f);
	t1.setString("");
	t1.setFillColor(Color::White);
	t1.setPosition(192, window.getSize().y - 160);
}

int ch = 1, ieye = 255;
float EyeTimer = 0, EyeDelay = 0.009;
bool BlinkCheck = true;
RectangleShape eye;
void GameScenes::blink()
{
	eye.setSize({ (float)window.getSize().x, (float)window.getSize().y });
	eye.setFillColor(Color(0, 0, 0, ieye));
	if (ieye >= 0 && BlinkCheck)
	{
		if (EyeTimer < 0)
		{
			EyeTimer = EyeDelay;
			ieye--;
			if (ieye == 110 && ch == 1)
				BlinkCheck = false, ch++;
			else if (ieye == 0 && ch == 2)
				IsBlinking = false;
		}
		else
		{
			EyeTimer -= DeltaTime;
		}
	}
	else if (!BlinkCheck)
	{
		if (EyeTimer < 0)
		{
			EyeTimer = EyeDelay;
			ieye++;
			if (ieye == 255)
				BlinkCheck = true, EyeDelay = 0.002;
		}
		else
		{
			EyeTimer -= DeltaTime;
		}
	}
	window.draw(eye);
}

int i1 = 0;
void GameScenes::scene1(enemies &e, rects &h)
{
	if (IsBlinking)
	{
		window.draw(e.sprite);
		window.draw(h.rect);
		blink();
	}
	else if (i1 < s1.size())
	{
		ChatTime = ChatDelay;
		DisplayText(t1, s1, i1, e, h, "hero");
	}
	else if (ChatTime > 0 && i1 == s1.size())
	{
		ChatTime -= DeltaTime;
		window.draw(e.sprite);
		window.draw(h.rect);
		window.draw(HeroTalk.rect);
		window.draw(t1);
	}
	else
	{
		ChatTime = ChatDelay;
		i1++;
		ieye = 255, ch = 1,EyeDelay = 0.009, IsBlinking = true;
		scene1ch = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		ChatTime = ChatDelay;
		i1++;
		ieye = 255, ch = 1, EyeDelay = 0.009, IsBlinking = true;
		scene1ch = 0;
	}
}

Text t2, t3, t4, t4_5, t5;
string s2, s3, s4, s4_5, s5;
void GameScenes::Scene2Set()
{
	s2 = "Do you think you can Defeat me, hhh, You are a useles pathetic weak hero who does not even deserve to be killed by my blade";
	s3 = "Egh, i will take revenge on my brother and defeat you at any cost";
	s4 = "HHHH, your brother is still alive, but you will never see him again";
	s4_5 = "What do you meen?!";
	s5 = "HaHaHaHa, FareWell, Hero!";
	t2.setFont(f);
	t3.setFont(f);
	t4.setFont(f);
	t4_5.setFont(f);
	t5.setFont(f);
	t2.setString("");
	t3.setString("");
	t4.setString("");
	t4_5.setString("");
	t5.setString("");
	t2.setFillColor(Color::White);
	t3.setFillColor(Color::White);
	t4.setFillColor(Color::White);
	t4_5.setFillColor(Color::White);
	t5.setFillColor(Color::White);
	t2.setPosition(192, window.getSize().y - 160);
	t3.setPosition(192, window.getSize().y - 160);
	t4.setPosition(192, window.getSize().y - 160);
	t4_5.setPosition(192, window.getSize().y - 160);
	t5.setPosition(window.getSize().x / 2 - 254, window.getSize().y / 2);
}

int i2 = 0, i3 = 0, i4 = 0, i4_5 = 0, i5 = 0, inap = 0;
float NapTimer = 0, NapDelay = 0.015;
RectangleShape nap;
void GameScenes::scene2(enemies& e, rects& h)
{
	nap.setSize({ (float)window.getSize().x, (float)window.getSize().y });
	nap.setFillColor(Color(0, 0, 0, inap));
	if (i2 < s2.size())
	{
		ChatTime = ChatDelay;
		DisplayText(t2, s2, i2, e, h, "FinalBoss");
	}
	else if (ChatTime > 0 && i2 == s2.size())
	{
		ChatTime -= DeltaTime;
		window.draw(e.sprite);
		window.draw(h.rect);
		window.draw(FinalBossTalk.sprite);
		window.draw(t2);
	}
	else if (i3 < s3.size())
	{
		ChatTime = ChatDelay;
		i2++;
		DisplayText(t3, s3, i3, e, h, "hero");
	}
	else if (ChatTime > 0 && i3 == s3.size())
	{
		ChatTime -= DeltaTime;
		window.draw(e.sprite);
		window.draw(h.rect);
		window.draw(HeroTalk.rect);
		window.draw(t3);
	}
	else if (i4 < s4.size())
	{
		ChatTime = ChatDelay;
		i3++;
		DisplayText(t4, s4, i4, e, h, "FinalBoss");
	}
	else if (ChatTime > 0 && i4 == s4.size())
	{
		ChatTime -= DeltaTime;
		window.draw(e.sprite);
		window.draw(h.rect);
		window.draw(FinalBossTalk.sprite);
		window.draw(t4);
	}
	else if (i4_5 < s4_5.size() || inap < 255)
	{
		ChatTime = ChatDelay;
		i4++;
		if (i4_5 < s4_5.size())
		{
			TextDelay = 0.15;
			DisplayText(t4_5, s4_5, i4_5, e, h, "hero");
			if (NapTimer < 0)
			{
				NapTimer = NapDelay;
				inap++;
			}
			else
			{
				NapTimer -= DeltaTime;
			}
			window.draw(nap);
		}
		else
		{
			TextDelay = 0.085;
			if (NapTimer < 0)
			{
				NapTimer = NapDelay;
				inap++;
			}
			else
			{
				NapTimer -= DeltaTime;
			}
			window.draw(e.sprite);
			window.draw(h.rect);
			window.draw(HeroTalk.rect);
			window.draw(t4_5);
			window.draw(nap);
		}
	}
	else if (ChatTime > 0 && inap == 255)
	{
		ChatTime -= DeltaTime;
		window.draw(e.sprite);
		window.draw(h.rect);
		window.draw(nap);
	}
	else if (i5 < s5.size())
	{
		inap++;
		ChatTime = ChatDelay;
		window.draw(nap);
		DisplayText(t5, s5, i5, e, h, "no");
	}
	else if (ChatTime > 0 && i5 == s5.size())
	{
		ChatTime -= DeltaTime;
		window.draw(nap);
		window.draw(t5);
	}
	else
	{
		ChatTime = ChatDelay;
		i5++;
		scene2ch = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		ChatTime = ChatDelay;
		i5++;
		scene2ch = 0;
	}
}

Text t6, t7, t8;
string s6, s7, s8;
void GameScenes::Scene3Set()
{
	s6 = "hmm, So you survived against my small monsters, hero";
	s7 = "I defeated them all, and now it is your turn, i will defeat you and get my brother back";
	s8 = "hahaha, come to your death you fool";
	t6.setFont(f);
	t7.setFont(f);
	t8.setFont(f);
	t6.setString("");
	t7.setString("");
	t8.setString("");
	t6.setFillColor(Color::White);
	t7.setFillColor(Color::White);
	t8.setFillColor(Color::White);
	t6.setPosition(192, window.getSize().y - 160);
	t7.setPosition(192, window.getSize().y - 160);
	t8.setPosition(192, window.getSize().y - 160);
}

int i6 = 0, i7 = 0, i8 = 0;
Vector2f Destance;
void GameScenes::scene3(enemies& e, rects& h)
{
	Destance = { (h.rect.getPosition().x - ((float)window.getSize().x / 4)),(h.rect.getPosition().y - ((float)window.getSize().y / 2)) };
	if (sqrt(Destance.x * Destance.x + Destance.y * Destance.y) > 3)
	{
		h.rect.move(-1.f * normalize(Destance) * 500.f * DeltaTime);	
		window.draw(e.sprite);
		window.draw(h.rect);
	}
	else if (i6 < s6.size())
	{
		ChatTime = ChatDelay;
		DisplayText(t6, s6, i6, e, h, "FinalBoss");
	}
	else if (ChatTime > 0 && i6 == s6.size())
	{
		ChatTime -= DeltaTime;
		window.draw(e.sprite);
		window.draw(h.rect);
		window.draw(FinalBossTalk.sprite);
		window.draw(t6);
	}
	else if (i7 < s7.size())
	{
		ChatTime = ChatDelay;
		i6++;
		DisplayText(t7, s7, i7, e, h, "hero");
	}
	else if (ChatTime > 0 && i7 == s7.size())
	{
		ChatTime -= DeltaTime;
		window.draw(e.sprite);
		window.draw(h.rect);
		window.draw(HeroTalk.rect);
		window.draw(t7);
	}
	else if (i8 < s8.size())
	{
		ChatTime = ChatDelay;
		i7++;
		DisplayText(t8, s8, i8, e, h, "FinalBoss");
	}
	else if (ChatTime > 0 && i8 == s8.size())
	{
		ChatTime -= DeltaTime;
		window.draw(e.sprite);
		window.draw(h.rect);
		window.draw(FinalBossTalk.sprite);
		window.draw(t8);
	}
	else
	{
		ChatTime = ChatDelay;
		i8++;
		scene3ch = 0;
	}
}

Text t9, t10;
string s9, s10;
void GameScenes::Scene4Set()
{
	s9 = "Okay Okay, you are strong, you win, i will take you to your friend";
	s10 = "hh, you better do";
	t9.setFont(f);
	t10.setFont(f);
	t9.setString("");
	t10.setString("");
	t9.setFillColor(Color::White);
	t10.setFillColor(Color::White);
	t9.setPosition(192, window.getSize().y - 160);
	t10.setPosition(192, window.getSize().y - 160);
}

int i9 = 0, i10 = 0;
void GameScenes::scene4(enemies& e, rects& h)
{
	if (!e.IsStanding)
	{
		FinalBossTalk.sprite.setTextureRect(IntRect(64 * 3, 64 * 20, 64, 64));
		if (i9 < s9.size())
		{
			ChatTime = ChatDelay;
			DisplayText(t9, s9, i9, e, h, "FinalBoss");
		}
		else if (ChatTime > 0 && i9 == s9.size())
		{
			ChatTime -= DeltaTime;
			window.draw(e.sprite);
			window.draw(h.rect);
			window.draw(FinalBossTalk.sprite);
			window.draw(t9);
		}
		else if (i10 < s10.size())
		{
			ChatTime = ChatDelay;
			i9++;
			DisplayText(t10, s10, i10, e, h, "hero");
		}
		else if (ChatTime > 0 && i10 == s10.size())
		{
			ChatTime -= DeltaTime;
			window.draw(e.sprite);
			window.draw(h.rect);
			window.draw(HeroTalk.rect);
			window.draw(t10);
		}
		else
		{
			ChatTime = ChatDelay;
			i10++;
			FinalBossTalk.sprite.setTextureRect(IntRect(0, 64 * 10, 64, 64));
			scene4ch = false;
		}
	}
	else
	{
		window.draw(e.sprite);
		window.draw(h.rect);
	}
}