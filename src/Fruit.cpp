#include "Fruit.h"

Fruit::Fruit()
{
  m_Collected = true;
  m_FrameCount = 0;
  m_BufferItr = 0;
}

Fruit::~Fruit() { }

void Fruit::AddAnimTexture(std::string txtrLocation)
{
  if(!m_FruitTexture.loadFromFile(txtrLocation))
  {
    std::cout << "Failed to load file" << std::endl;
  }
  else
  {
    m_TxtrAnimBuff.push_back(m_FruitTexture);
  }
}

void Fruit::SetCollectable(bool b) { m_Collected = b; }

bool Fruit::GetCollectable() { return m_Collected; }

void Fruit::SetPosition(int x, int y)
{
  m_Position.x = x;
  m_Position.y = y;
  m_FruitSprite.setPosition(m_Position.x, m_Position.y);
}

sf::Vector2f Fruit::GetPosition() const { return m_Position; }

sf::Vector2f Fruit::GetSize() const
{
  return { m_FruitSprite.getGlobalBounds().width, m_FruitSprite.getGlobalBounds().height };
}

void Fruit::HandleAnimTexture()
{
  int bufferStart = 0;
  int bufferEnd = m_TxtrAnimBuff.size() - 1;

  std::cout << "BufferItr is: " << m_BufferItr << std::endl;
  std::cout << "Buffer End value is: " << bufferEnd << std::endl;
  if(m_FrameCount > 60)
  {
    m_FrameCount = 0;
  }

  if(bufferEnd > 1)
  {
    if(m_FrameCount == 0 )
    {
      m_FruitSprite.setTexture(m_TxtrAnimBuff[m_BufferItr]);

      CheckBuffItr(bufferStart, bufferEnd);
    }
    else if(m_FrameCount == 10)
    {
      m_FruitSprite.setTexture(m_TxtrAnimBuff[m_BufferItr]);

      CheckBuffItr(bufferStart, bufferEnd);
    }
    else if(m_FrameCount == 20)
    {
      m_FruitSprite.setTexture(m_TxtrAnimBuff[m_BufferItr]);

      CheckBuffItr(bufferStart, bufferEnd);
    }
    else if(m_FrameCount == 30)
    {
      m_FruitSprite.setTexture(m_TxtrAnimBuff[m_BufferItr]);

      CheckBuffItr(bufferStart, bufferEnd);
    }
    else if(m_FrameCount == 40)
    {
      m_FruitSprite.setTexture(m_TxtrAnimBuff[m_BufferItr]);

      CheckBuffItr(bufferStart, bufferEnd);
    }
    else if(m_FrameCount == 50)
    {
      m_FruitSprite.setTexture(m_TxtrAnimBuff[m_BufferItr]);

      CheckBuffItr(bufferStart, bufferEnd);
    }
    else if(m_FrameCount == 60)
    {
      m_FruitSprite.setTexture(m_TxtrAnimBuff[m_BufferItr]);

      CheckBuffItr(bufferStart, bufferEnd);
    }
  }
  else
  {
    m_FruitSprite.setTexture(m_TxtrAnimBuff[0]);
  }

  //m_FruitSprite.setTexture(m_TxtrAnimBuff[2])// else
  // {
  //   m_FruitSprite.setTexture(m_TxtrAnimBuff[0]);
  // };
  m_FrameCount++;

}

void Fruit::CheckBuffItr(int start, int end)
{
  if(m_PreviousBuffItr < m_BufferItr)
  {
    m_PreviousBuffItr = m_BufferItr;
    m_BufferItr++;
  }
  else if(m_PreviousBuffItr > m_BufferItr)
  {
    m_PreviousBuffItr = m_BufferItr;
    m_BufferItr--;
  }

  if(m_BufferItr < start)
  {
    m_PreviousBuffItr = m_BufferItr;
    m_BufferItr = start;
  }
  else if(m_BufferItr > end)
  {
      m_PreviousBuffItr = m_BufferItr;
      m_BufferItr = end;
  }
}

void Fruit::Draw(Window& win)
{
  HandleAnimTexture();
  win.Draw(m_FruitSprite);
}
