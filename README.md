# 🎬 AI Movie Quiz Game (C + GPT via OpenRouter)

Welcome to the **AI-Powered Movie Quiz Game**!  
This is a fun console-based C program that quizzes you on movie trivia by using AI-generated questions via OpenRouter + GPT.

---

## 🤖 How It Works

- The C program calls a Python script.
- The Python script uses the OpenRouter API to fetch a random movie trivia question from GPT-3.5.
- The question is returned as JSON and parsed in C.
- You answer — and the app tells you if you're right or wrong!

---

## 🧩 Files in This Repo

| File | Description |
|------|-------------|
| `main.c` | The main quiz program written in C |
| `generate_question.py` | A Python script that fetches a quiz question from GPT |
| `question.txt` | A temp file used by C to read the Python-generated question |

---

## 🚀 Setup Instructions

### ✅ Requirements

- Python 3.x
- A C compiler (like GCC or Code::Blocks)
- An OpenRouter API Key (Get one from [https://openrouter.ai](https://openrouter.ai))
- Internet connection

### 🔧 Install Python Dependencies

```bash
pip install openai
