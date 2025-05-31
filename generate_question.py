import openai
import sys
import json

sys.stdout.reconfigure(encoding='utf-8')

client = openai.OpenAI(
    api_key="YOUR_API_KEY",
    base_url="https://openrouter.ai/api/v1"
)

# Ask GPT to return clean JSON — without letter labels in options
response = client.chat.completions.create(
    model="openai/gpt-3.5-turbo",
    messages=[
        {
            "role": "system",
            "content": "You are a movies quiz generator. ONLY return raw JSON, without any explanation or labels in the answer choices."
        },
        {
            "role": "user",
            "content": "Generate a multiple choice movies quiz question with exactly 4 options. Respond ONLY with raw JSON with keys: 'question' (string), 'options' (list of 4 strings), and 'correct' (A/B/C/D). Do NOT label options like 'A. Option text'. Just the option text."
        }
    ]
)

# Ensure valid JSON output
try:
    raw_content = response.choices[0].message.content.strip()

    # Strip markdown if present
    if raw_content.startswith("```"):
        raw_content = raw_content.strip("` \n")
        if raw_content.startswith("json"):
            raw_content = raw_content[4:].strip()

    # Parse and pretty-print valid JSON
    parsed = json.loads(raw_content)
    print(json.dumps(parsed, indent=2))

except Exception as e:
    print(json.dumps({"error": "Failed to parse response", "details": str(e)}))
