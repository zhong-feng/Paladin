#include "CBagDirector.h"

#include "CBagScene.h"
#include "CQiuDao.h"
#include "CYaHui.h"

int CBagDirector::money = 0;

 CBagDirector::CBagDirector()
{
    m_pBag = 0;
    pointOfBagStartRender = CPosition(0, 0);
    pointOfShowItemInfo = CPosition(0, 0);
    pointOfShowHelpInfo = CPosition(0, 0);

    //背包系统的初始化
    onInit();
}

  CBagDirector::~CBagDirector()
 {
     if (m_pBag)
     {
         delete m_pBag;
         m_pBag = 0;
     }
 }

  //进入背包系统

   int CBagDirector::enterBagSystem()
  {
       //打印帮助信息
       renderHelpInfo();

      //背包系统的渲染更新--------------
      renderBagSystemUI();

      while (true)
      {

          int keyCode = _getch();
          switch (keyCode)
          {

          case 'a':
          case 'A': { moveSelectedCursor(DI_LEFT);  break; }  //移动选择光标
          case 'd':
          case 'D': { moveSelectedCursor(DI_RIGHT);  break; }
          case 'w':
          case 'W': { moveSelectedCursor(DI_UP);  break; }
          case 's':
          case 'S': { moveSelectedCursor(DI_DOWN);  break; }

          case '1': { randomAddItem();  break; }//随机添加物品

          case '\r': { enterSelectedCurosor();  break; }//使用物品

          case 'n':
          case 'N':{ eraserItemInfo(); return 1; break; }   // n 切换到商店
          case '\t':{ eraserItemInfo(); return 10; break; }  // TAB 切换选项卡

          case 27: { eraserItemInfo(); return -1; }  //Esc -- 退出背包系统
          }

          //背包系统的的渲染更新
          renderBagSystemUI();
      }

  }

    int CBagDirector::getMoney()
   {
       return money;
   }

     void CBagDirector::setMoney(int _num)
    {
        money = _num;
    }

   //背包系统的渲染更新--------------

    void CBagDirector::renderBagSystemUI()
    {
        //打印背包信息
        renderBag();

        //打印金钱
        CUtils::gotoXY(pointOfShowItemInfo+DI_UP);
        cout << "现有金钱  " << money << endl;;

        //打印选择光标
       selectedCursor.render(pointOfBagStartRender + selectedCursor.pos);

       //打印物品提示信息
       displaySelectedItemInfo();
   }

//使用光标选择的物品
 void CBagDirector::useTheSelectedCursorItem()
{
    //确定使用的物品ID
    auto useItemID = m_pBag->useItem(selectedCursor.pos);

    //不可以使用的物品直接返回
    if (useItemID == ID_None)
    {
        return;
    }

    //1.确认使用对象-----------------------------------

    //渲染 选择 对象画面(返回可选数量 默认选求仙)
    int maxCount = renderChoiceUIScene();
    int choiceNum = 0;

    //确认选择对象
    CUtils::moveSelectedUpOrDown(choiceNum, maxCount, CPosition(BAGPROMPTPOSX + 2, BAGPROMPTPOSY + 2), 124, 193);

    //擦除选择画面
    eraserChoiceUIScene();

    CRole* tmpRole = nullptr;
    if (choiceNum == 0)
    {
        tmpRole = CQiuDao::getInstance();
    }
    else
    {
        tmpRole = CYaHui::getInstance();
    }

    // 2. 确认使用 结果----------------------
    auto tmpIten = CItemFactory::createItem(useItemID);

    switch (tmpIten->type)
    {
    case IT_Drug: { tmpIten->useItem(tmpRole); break; }
    case IT_Weapon: {useWeapon(tmpIten, tmpRole); break; }
    case IT_Garment: { useGarment(tmpIten, tmpRole); break; }
    default: break;
    }

    
    delete tmpIten;
    tmpIten = 0;
}

 //擦除选择画面
void CBagDirector::eraserChoiceUIScene()
 {
    eraserMessageUIScence();
 }

//背包系统的初始化

 void CBagDirector::onInit()
{
    //从背包场景提取背包坐标数据
    CBagScene* tmpScene = new CBagScene();

    //背包打印的坐标
    pointOfBagStartRender = tmpScene->getScenePoint()+CPosition(0,1);
    pointOfShowItemInfo = tmpScene->getStatePoint() + CPosition(0, 1);
    pointOfShowHelpInfo = tmpScene->getHelpPoint();

    //光标默认在第一个位置
    selectedCursor.pos = CPosition(1, 1);

    //创建背包对象
    m_pBag = new CBag();

    delete tmpScene;
    tmpScene = 0;
}

//渲染 选择 对象画面(返回可选数量)
int CBagDirector::renderChoiceUIScene()
{
    renderMessageUIScence();

    //渲染 求仙

    //确定颜色
    CUtils::setColor(110);

    CUtils::gotoXY(CPosition( BAGPROMPTPOSX + 2, BAGPROMPTPOSY + 3 ));
    cout << CQiuDao::getInstance()->getName();

    int max = 1;

    //渲染 雅惠

    //确认位置
    CUtils::gotoXY(CPosition( BAGPROMPTPOSX + 3, BAGPROMPTPOSY + 3 ));

    //确认跟随队伍
    if (CYaHui::getInstance()->getIsShow())
    {
        max++;
    }
    else
    {
        //确定颜色
        CUtils::setColor(103);
    }
    cout << CYaHui::getInstance()->getName();

    //默认选择 求仙
    CUtils::setColor(193);
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 2, BAGPROMPTPOSY + 2 ));
    cout << "→" << endl;

    CUtils::setColor();

    return max;
}

void CBagDirector::renderBag()
{
    //背包的渲染
    m_pBag->renderBagUI(pointOfBagStartRender);
}

void CBagDirector::enterSelectedCurosor()
{
    //先确认物品可以操作
    auto tmpItemID = m_pBag->getBagUnit(selectedCursor.pos)->getID();
    if (tmpItemID == ID_None)
    {
        return;
    }

    //渲染 选择 做什么
    renderMessageUIScence();

    //可选列表（返回可选最大值）
    int maxNum = renderCanChoiceList();
    int choiceNum = 0;

    //确认选择对象
    CUtils::moveSelectedUpOrDown(choiceNum, maxNum, CPosition(BAGPROMPTPOSX + 1, BAGPROMPTPOSY + 2), 124, 193);

    //擦除 选择 画面
    eraserMessageUIScence();

    switch (choiceNum)
    {
    case 0: {return; break; }//返回
    case 1: {saleItem(); break; }//出售
    case 2: {castOffItem(); break; }//丢弃
    case 3: {useTheSelectedCursorItem(); break; }//使用
    default: break;
    }

    return;
}

void CBagDirector::castOffItem()
{
    //确定单元格
    auto tmpBagUnit = m_pBag->getBagUnit(selectedCursor.pos);

    //更改单元格数据 丢弃物品
    tmpBagUnit->setCount(0);
    tmpBagUnit->setID(ID_None);
}

void CBagDirector::saleItem()
{
    auto tmpBagUnit = m_pBag->getBagUnit(selectedCursor.pos);

    //确定数量
    auto tmpNum = tmpBagUnit->getCount();

    //确定单价
    auto tmpItem = CItemFactory::createItem(tmpBagUnit->getID());
    auto tmpSellPrice = tmpItem->sellPrice;

    //释放临时数据
    delete tmpItem;
    tmpItem = 0;

    money += tmpSellPrice * tmpNum;

    tmpBagUnit->setCount(0);
    tmpBagUnit->setID(ID_None);

    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\sell.wma");

}

int CBagDirector::renderCanChoiceList()
{
    //确定颜色
    CUtils::setColor(110);

    //确定可选项打印坐标
    CPosition tmpPos = CPosition(BAGPROMPTPOSX + 1, BAGPROMPTPOSY + 3);

    //定义变量保存可选数量
    int tmpMaxNum = 0;

    CUtils::gotoXY(tmpPos);
    cout << "返回";
    tmpMaxNum++;
    tmpPos = tmpPos + DI_DOWN;

    CUtils::gotoXY(tmpPos);
    cout << "出售";
    tmpMaxNum++;
    tmpPos = tmpPos + DI_DOWN;

    CUtils::gotoXY(tmpPos);
    cout << "丢弃";
    tmpMaxNum++;
    tmpPos = tmpPos + DI_DOWN;

    //确定是否可以使用
    auto tmpItemID = m_pBag->getBagUnit(selectedCursor.pos)->getID();
    if (tmpItemID > 0 && tmpItemID < ID_Apple)
    {
        CUtils::gotoXY(tmpPos);
        cout << "使用";
        tmpMaxNum++;
    }

    //选择第一个为默认选择项
    //默认选择 求仙
    CUtils::setColor(193);
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 1, BAGPROMPTPOSY + 2));
    cout << "→" << endl;

    CUtils::setColor();

    return tmpMaxNum;
}

void CBagDirector::useWeapon(CItem* _weapon, CRole* _role)
{
    //将已装备的武器卸下
    if (_role->getWeaponID() != ID_None)
    {
        auto tmpItem = CItemFactory::createItem(_role->getWeaponID());

        tmpItem->putDownEquipment(_role);

        m_pBag->addItem(tmpItem->id);

        delete tmpItem;
        tmpItem = 0;
    }

    //装备武器
    _weapon->useItem(_role);
    _role->setWeaponID(_weapon->id);
}

void CBagDirector::useGarment(CItem* _garment, CRole* _role)
{
    //将已装备的 防具 卸下
    if (_role->getGarmentID() != ID_None)
    {
        auto tmpItem = CItemFactory::createItem(_role->getGarmentID());

        tmpItem->putDownEquipment(_role);
        m_pBag->addItem(tmpItem->id);

        delete tmpItem;
        tmpItem = 0;
    }

    //装备 防具
    _garment->useItem(_role);
    _role->setGarmentID(_garment->id);
}

void CBagDirector::renderMessageUIScence()
{
    //确定颜色
    CUtils::setColor(124);

    //渲染边框 背景
    for (int i = 0; i < COLOFMESSAGE; i++)
    {
        for (int j = 0; j < ROWOFMESSAGE; j++)
        {
            CUtils::gotoXY(CPosition(BAGPROMPTPOSX + i, BAGPROMPTPOSY + j));
            if (i == 0 || i == COLOFMESSAGE - 1)
            {
                cout << "==";
                continue;
            }
            if (j == 0 || j == ROWOFMESSAGE - 1)
            {
                cout << "||";
                continue;
            }

            cout << "  ";
        }
    }

    CUtils::setColor();
}

void CBagDirector::eraserMessageUIScence()
{
    CUtils::setColor();

    for (int i = 0; i < COLOFMESSAGE; i++)
    {
        for (int j = 0; j < ROWOFMESSAGE; j++)
        {
            CUtils::gotoXY(CPosition(BAGPROMPTPOSX + i, BAGPROMPTPOSY + j));
            cout << "  ";
        }
    }
}

void CBagDirector::randomAddItem()
{
    int randomItem = (rand()*rand() + rand()) % 7;
    int randomNum = (rand()*rand() + rand()) % 3 + 1;

    switch (randomItem)
    {
    case 0: { m_pBag->addItem(ID_HP, randomNum); break; }
    case 1: { m_pBag->addItem(ID_MP, randomNum); break; }
    case 2: { m_pBag->addItem(ID_Sword, randomNum); break; }
    case 3: { m_pBag->addItem(ID_Whips, randomNum); break; }
    case 4: { m_pBag->addItem(ID_Ioricae, randomNum); break; }
    case 5: { m_pBag->addItem(ID_Sackcloth, randomNum); break; }
    case 6: { m_pBag->addItem(ID_Apple, randomNum); break; }

    default: break;
    }
}

void CBagDirector::moveSelectedCursor(CDirection _direction)
{
    CPosition nextPos = selectedCursor.pos + _direction;

    //边界判断
    if (nextPos.x < 1 || nextPos.x > m_pBag->getRow() - 2
        || nextPos.y < 1 || nextPos.y > m_pBag->getCol() - 2)
    {
        return;
    }
    else
    {
        selectedCursor.pos = nextPos;
    }
}

void CBagDirector::eraserItemInfo()
{
    for (int i = 0; i < 10; i++)
    {
        CUtils::gotoXY(pointOfShowItemInfo.getX() + i, pointOfShowItemInfo.getY() * 2);
        cout << "                    ";
    }
}

void CBagDirector::renderHelpInfo()
{
    //设定颜色
    CUtils::setColor(COLEROFHELP);

    CUtils::gotoXY(pointOfShowHelpInfo.getX(), pointOfShowHelpInfo.getY() * 2);
    cout << "    帮助信息";

    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 2, pointOfShowHelpInfo.getY() * 2);
    cout << "  光标移动: ";

    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 3, pointOfShowHelpInfo.getY() * 2);
    cout << "  左/右    A/D";
    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 4, pointOfShowHelpInfo.getY() * 2);
    cout << "  上/下    W/S";

    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 6, pointOfShowHelpInfo.getY() * 2);
    cout << "   确 认   Enter";
    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 7, pointOfShowHelpInfo.getY() * 2);
    cout << "   退 出   ESC";

    //颜色改回默认值
    CUtils::setColor();
}

void CBagDirector::displaySelectedItemInfo()
{
    //清空之前的渲染
    eraserItemInfo();

    //确定单元格
    auto tmpBagUnit = m_pBag->getBagUnit(selectedCursor.pos);

    //根据单元格确定物品
    auto pTmpItem = CItemFactory::createItem(tmpBagUnit->getID());

    if (tmpBagUnit->getCount() == 0)
    {
        CUtils::gotoXY(pointOfShowItemInfo);
        cout << "空";
    }
    else
    {
        CUtils::gotoXY(pointOfShowItemInfo);
        cout << "数量  " << tmpBagUnit->getCount() << endl;

        pTmpItem->renderItemInfo(pointOfShowItemInfo + DI_DOWN);
    }

    delete pTmpItem;
    pTmpItem = 0;
}

CBag* CBagDirector::getBag()
{
    return m_pBag;
}
