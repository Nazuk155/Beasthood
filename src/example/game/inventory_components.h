//
// Created by Prince of Brass on 03.02.2025.
//
#pragma once
#include "../global.hpp"
#include "item.h"
//#include "layout.h"
#include "character.h"



#ifndef SDL_BASE_INVENTORY_COMPONENTS_H
#define SDL_BASE_INVENTORY_COMPONENTS_H

struct InventoryIcon //maybe not
{
  bool active = false;
  SDL_Rect position{};
  Item* referencedItem = nullptr;
  SDL_Texture* iconImg = nullptr;
};



struct
{
    SDL_Point StartPoint;
    SDL_Point Dimensions {15,15};



    //String Name = referencedItem->GetName(); //possibly redundant? more readable
    //String Text; //todo add descriptions/loretext to items

    SDL_Point EquipLeftPos{1,11};
    SDL_Point EquipRightPos {9,11};
    SDL_Point ButtonScale {5,3};
    //Button EquipRight;
    //Button EquipLeft;

} ItemDetailedView;

inline void RenderItemIcon(SDL_Renderer*renderer,const Item* item,SDL_Texture* baseIcon, const std::vector<SDL_Texture*>& iconVector, const SDL_Rect iconScale, const SDL_Rect& destinationRect) {
    switch (item->GetItemID()) {


        case ItemID::Halberd:
            SDL_RenderCopy(renderer, iconVector[1], &iconScale, &destinationRect
            );
            break;
        case ItemID::HalberdMaster:
            SDL_RenderCopy(renderer, iconVector[1], &iconScale, &destinationRect
            );
            break;
        case ItemID::PrayerBook:
            SDL_RenderCopy(renderer, iconVector[2], &iconScale, &destinationRect
            );
            break;
        case ItemID::Candle:
            SDL_RenderCopy(renderer, iconVector[3], &iconScale, &destinationRect
            );
            break;
        case ItemID::Torch:
            SDL_RenderCopy(renderer, iconVector[4], &iconScale, &destinationRect
            );
            break;
        case ItemID::GUN:
            SDL_RenderCopy(renderer, iconVector[5], &iconScale, &destinationRect
            );
            break;
        case ItemID::RitualSkullCursed:
            SDL_RenderCopy(renderer, iconVector[6], &iconScale, &destinationRect
            );
            break;
        case ItemID::BulletLead:
            SDL_RenderCopy(renderer, iconVector[7], &iconScale, &destinationRect
            );
//Todo text to texture?
            break;
        case ItemID::BulletSilver:
            SDL_RenderCopy(renderer, iconVector[8], &iconScale, &destinationRect
            );
            break;
        case ItemID::LoadedGunLead:
            SDL_RenderCopy(renderer, iconVector[9], &iconScale, &destinationRect
            );
            break;
        case ItemID::LoadedGunSilver:
            SDL_RenderCopy(renderer, iconVector[10], &iconScale, &destinationRect
            );
            break;
        case ItemID::Relic:
            SDL_RenderCopy(renderer, iconVector[11], &iconScale, &destinationRect
            );
            break;
        case ItemID::Sword:
            SDL_RenderCopy(renderer, iconVector[12], &iconScale, &destinationRect
            );
            break;
        case ItemID::Honorius:
            SDL_RenderCopy(renderer, iconVector[13], &iconScale, &destinationRect
            );
            break;
        case ItemID::Talisman:
            SDL_RenderCopy(renderer, iconVector[14], &iconScale, &destinationRect
            );
            break;
        default:
            SDL_RenderCopy(renderer, iconVector[0], &iconScale, &destinationRect
            );
            break;
    }
}


class InventoryPage
{

    //8x*5y icons - 40?
public:
    Character* currentCharacter = nullptr; //todo this is a mess
    std::vector<InventoryIcon> icons;
    SDL_Point StartPoint{20,20};
    SDL_Point Dimensions{60,66};
    InventoryIcon* MouseOverIcon = nullptr;

    bool bIconHover = false;
    bool bIconSelected = false;

//public:
    void RenderInventoryPage(SDL_Renderer*renderer, int screenWidth, int screenHeight, SDL_Texture* baseIcon, const std::vector<SDL_Texture*>& iconVector, const SDL_Rect iconScale)
    {
        SDL_Rect window = {static_cast<int>(StartPoint.x*screenWidth*0.01), static_cast<int>(StartPoint.y*screenHeight*0.01),
                           static_cast<int>(Dimensions.x*screenWidth*0.01),static_cast<int>(Dimensions.y*screenHeight*0.01)};

        SDL_SetRenderDrawColor(renderer,2,2,2,0);
        SDL_RenderFillRect(renderer,&window);
        //iterate icons
        SDL_Rect icon {0,
                       0,
                       static_cast<int>(0.07*screenWidth),
                       static_cast<int>(0.07*screenWidth)
        };
        bool bIconsLoaded = true;
        for(SDL_Texture * icon:iconVector)
        {
            if (!icon)
            {
                fmt::println("Failed to load icon");
                bIconsLoaded= false;
            }

        }
        for(int i = 0; i < 8; i++)
        {
            for(int j=0;j<5;j++)
            {
                icon.x=static_cast<int>(window.x + ((0.0025+0.0725)*screenWidth)*i);
                icon.y=static_cast<int>(window.y + ((0.0025+0.0725)*screenWidth)*j);
                icons[i+8*j].position=icon;


                if (icons[i + 8 * j].active) {
                    if (bIconsLoaded) {

                        RenderItemIcon(renderer,icons[i + 8 * j].referencedItem,baseIcon,iconVector,iconScale,icon);
//                        switch (icons[i + 8 * j].referencedItem->GetItemID()) {
//
//                            case ItemID::Halberd:
//                                SDL_RenderCopy(renderer, iconVector[1], &iconScale, &icon);
//                                break;
//                            case ItemID::PrayerBook:
//                                SDL_RenderCopy(renderer, iconVector[2], &iconScale, &icon);
//                                break;
//                            case ItemID::Candle:
//                                SDL_RenderCopy(renderer, iconVector[3], &iconScale, &icon);
//                                break;
//                            case ItemID::Torch:
//                                SDL_RenderCopy(renderer, iconVector[4], &iconScale, &icon);
//                                break;
//                            case ItemID::GUN:
//                                SDL_RenderCopy(renderer, iconVector[5], &iconScale, &icon);
//                            case ItemID::RitualSkull:
//                                SDL_RenderCopy(renderer, iconVector[6], &iconScale, &icon);
//                            default:
//                                SDL_RenderCopy(renderer, iconVector[0], &iconScale, &icon);
//                                break;
//                        }

                    } else {
                        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 0);
                        SDL_RenderFillRect(renderer, &icon);
                    }


                }
                else
                {
                    SDL_Rect  sourceRect {0,0,67,67};
                    SDL_RenderCopy(renderer,baseIcon,&sourceRect,&icon);
                    //SDL_SetRenderDrawColor(renderer,10,10,10,0);
                    //SDL_RenderFillRect(renderer,&icon);
                }
            }
        }

    }
    void MouseOver(int mouseX, int mouseY)
    {

        //iterate over icons
        for(InventoryIcon &icon : icons)
        {
            if(mouseX >= icon.position.x && mouseX < (icon.position.x + icon.position.w) &&
               mouseY >= icon.position.y && mouseY < (icon.position.y + icon.position.h) &&
               icon.active && !bIconSelected) //mouse in icon, icon has meaning and not clicked
            {

                MouseOverIcon=&icon;
                bIconHover=true;
                return;

            }
            else
            {
                if(!bIconSelected)
                    MouseOverIcon = nullptr;
                bIconHover=false;

            }
        }
        //no else, hovering nowhere is irrelevant
    }

};

class InventoryScreen
{

    std::vector<InventoryPage> pages;
    public:
    Character* currentCharacter = nullptr;
    InventoryPage currentPage;


    //on init and update -> calculate pages
    InventoryScreen()
    {
        currentCharacter= nullptr;
    }
    explicit InventoryScreen(Character* chara)
    {

        currentCharacter = chara;
        BuildInventory();




    }

    void BuildInventory() //TODO currently 40 item max, build other pages, deal with potential memory leak form that expansion
    {


        currentPage.currentCharacter = currentCharacter;


        SDL_Rect iconRect {0,0,
                           0,
                           0};
        for(int j=0;j<5;j++)
        {
            for(int i = 0; i < 8; i++)
            {
                if(i+8*j < currentCharacter->GetInventory().size()) //todo screenwidth currently in Render()-> move to constructor params?
                    // get item
                {

                    currentPage.icons.push_back(InventoryIcon{true,iconRect,currentCharacter->GetInventory()[i+8*j]});

                }
                else
                {
                    //empty icon
                    currentPage.icons.push_back(InventoryIcon{false,iconRect, nullptr});
                }

            }
        }

    }
    void RebuildInventory()
    {
        SDL_Rect iconRect {0,0,
                           0,
                           0};
        for(int j=0;j<5;j++)
        {
            for(int i = 0; i < 8; i++)
            {
                if(i+8*j < currentCharacter->GetInventory().size()) //todo screenwidth currently in Render()-> move to constructor params?
                    // get item
                {
                    currentPage.icons[i+8*j]=InventoryIcon{true,iconRect,currentCharacter->GetInventory()[i+8*j]};


                }
                else
                {
                    //empty icon
                    currentPage.icons[i+8*j]=InventoryIcon{false,iconRect, nullptr};

                }

            }
        }
    }



    void Click(int mouseX, int mouseY, int screenWidth, int screenHeight, ItemManager* itemManager)
    {

        if(currentPage.bIconSelected && currentPage.MouseOverIcon->referencedItem->GetHandsNeeded()!=0 && !currentPage.MouseOverIcon->referencedItem->isBullet)
        {
            //fmt::println("Clicked while selection locked");


            SDL_Rect ButtonRect //Right
                    ={
                            static_cast<int>((screenWidth*0.01)*(currentPage.StartPoint.x -ItemDetailedView.Dimensions.x + ItemDetailedView.EquipRightPos.x)),
                            static_cast<int>((screenHeight*(currentPage.StartPoint.y )*0.01)+ItemDetailedView.EquipRightPos.y*0.01*screenWidth),
                            static_cast<int>(ItemDetailedView.ButtonScale.x*0.01*screenWidth),
                            static_cast<int>(ItemDetailedView.ButtonScale.y*0.01*screenWidth)

                    };
            if(mouseX >= ButtonRect.x && mouseX < (ButtonRect.x + ButtonRect.w) &&
               mouseY >= ButtonRect.y && mouseY < (ButtonRect.y + ButtonRect.h))
            {
                fmt::println("click right");
                if(currentCharacter->GetEquipment().second)
                {
                    fmt::println("unequipping second");
                    currentCharacter->UnequipItem(currentCharacter->GetEquipment().second->GetItemID());
                }
                if(currentCharacter->GetEquipment().first && (currentPage.MouseOverIcon->referencedItem->GetHandsNeeded()==2 || currentCharacter->GetEquipment().first->GetHandsNeeded()==2))
                {
                    fmt::println("unequipping first");
                    currentCharacter->UnequipItem(currentCharacter->GetEquipment().first->GetItemID());
                }

                currentCharacter->EquipItem(currentPage.MouseOverIcon->referencedItem);
                fmt::println("click past checks - to equip");
                //fmt::println("Clicked equip {} in Right Hand",currentCharacter->GetEquipment().second->GetName());
                fmt::println("click past equip");
                RebuildInventory();
                currentCharacter->UpdateCurrentStats();

                //prevent 'empty item' being displayed/handled
                currentPage.MouseOverIcon = nullptr;
                currentPage.bIconHover=false;
                currentPage.bIconSelected = false;

                return;
            }

            ButtonRect //Left
                    ={
                    static_cast<int>((screenWidth*0.01)*(currentPage.StartPoint.x -ItemDetailedView.Dimensions.x + ItemDetailedView.EquipLeftPos.x)),
                    static_cast<int>((screenHeight*(currentPage.StartPoint.y )*0.01)+ItemDetailedView.EquipRightPos.y*0.01*screenWidth),
                    static_cast<int>(ItemDetailedView.ButtonScale.x*0.01*screenWidth),
                    static_cast<int>(ItemDetailedView.ButtonScale.y*0.01*screenWidth)

            };
            if(mouseX >= ButtonRect.x && mouseX < (ButtonRect.x + ButtonRect.w) &&
               mouseY >= ButtonRect.y && mouseY < (ButtonRect.y + ButtonRect.h))
            {
                fmt::println("click left");
                if(currentCharacter->GetEquipment().first)
                {
                    fmt::println("unequipping first");
                    currentCharacter->UnequipItem(currentCharacter->GetEquipment().first->GetItemID());

                }
                if(currentCharacter->GetEquipment().second && (currentPage.MouseOverIcon->referencedItem->GetHandsNeeded()==2 || currentCharacter->GetEquipment().second->GetHandsNeeded()==2))
                {
                    fmt::println("unequipping second");
                    currentCharacter->UnequipItem(currentCharacter->GetEquipment().second->GetItemID());

                }
                fmt::println("click past checks - to equip");
               // fmt::print("Clicked equip {} in Left Hand",currentPage.MouseOverIcon->referencedItem->GetName());
                currentCharacter->EquipItem(currentPage.MouseOverIcon->referencedItem);
                fmt::println("click past equip");
                RebuildInventory();
                currentCharacter->UpdateCurrentStats();

                //prevent 'empty item' being displayed/handled
                currentPage.MouseOverIcon = nullptr;
                currentPage.bIconHover=false;
                currentPage.bIconSelected = false;

                return;
            }




        }
        else if(currentPage.bIconSelected && currentPage.MouseOverIcon->referencedItem->GetHandsNeeded() == 0 &&currentPage.MouseOverIcon->referencedItem->isBullet)
        {
            fmt::println("click bullet");
            SDL_Rect ButtonRect //Left?
                    ={
                            static_cast<int>((screenWidth*0.01)*(currentPage.StartPoint.x -ItemDetailedView.Dimensions.x + ItemDetailedView.EquipRightPos.x)),
                            static_cast<int>((screenHeight*(currentPage.StartPoint.y )*0.01)+ItemDetailedView.EquipRightPos.y*0.01*screenWidth),
                            static_cast<int>(ItemDetailedView.ButtonScale.x*0.01*screenWidth),
                            static_cast<int>(ItemDetailedView.ButtonScale.y*0.01*screenWidth)

                    };
            if(mouseX >= ButtonRect.x && mouseX < (ButtonRect.x + ButtonRect.w) &&
               mouseY >= ButtonRect.y && mouseY < (ButtonRect.y + ButtonRect.h))
            {
                fmt::println("click left-bullet");

                //is the gun equipped?
                bool bGunPresent = false;
                bool bGunWasEquipped = false;
                bool bGunFirst = false;
                if(currentCharacter->GetEquipment().first && currentCharacter->GetEquipment().first->GetItemID()==ItemID::GUN)
                {
                    currentCharacter->UnequipItem(ItemID::GUN);
                    bGunPresent=true;
                    bGunWasEquipped=true;
                    bGunFirst=true;
                }
                else if(currentCharacter->GetEquipment().second && currentCharacter->GetEquipment().second->GetItemID()==ItemID::GUN)
                {
                    currentCharacter->UnequipItem(ItemID::GUN);
                    bGunPresent=true;
                    bGunWasEquipped=true;
                    bGunFirst= false;
                }
                //is the gun in the inventory?
                if(!bGunWasEquipped)
                {
                    for (Item* i: currentCharacter->GetInventory())
                    {
                        if(i->GetItemID()==ItemID::GUN)
                        {
                            bGunPresent = true;
                        }
                    }
                }
                //we have a gun! switch it with the loaded one
                if (bGunPresent)
                {
                    currentCharacter->RemoveFromInventory(ItemID::GUN);
                    switch (currentPage.MouseOverIcon->referencedItem->GetItemID()) {
                        case(ItemID::BulletSilver):
                            fmt::println("loading silver bullet");
                            currentCharacter->RemoveFromInventory(currentPage.MouseOverIcon->referencedItem->GetItemID());



                            //prevent 'empty item' being displayed/handled
                            currentPage.MouseOverIcon = nullptr;
                            currentPage.bIconHover=false;
                            currentPage.bIconSelected = false;
                            //equip or add?
                            if(bGunWasEquipped)
                            {
                                //equip
                                currentCharacter->EquipItem(itemManager->GetItem(ItemID::LoadedGunSilver));
                            }
                            else
                            {
                                //add
                                currentCharacter->AddToInventory(itemManager->GetItem(ItemID::LoadedGunSilver));
                            }


                            RebuildInventory();
                            currentCharacter->UpdateCurrentStats();

                            break;
                        default:
                            fmt::println("loading lead bullet");
                            if(currentCharacter->leadBulletCount ==1) {
                                currentCharacter->RemoveFromInventory(
                                        currentPage.MouseOverIcon->referencedItem->GetItemID());
                                currentCharacter->leadBulletCount--;
                            }
                            else
                            {
                                currentCharacter->leadBulletCount--;
                            }



                            //prevent 'empty item' being displayed/handled
                            currentPage.MouseOverIcon = nullptr;
                            currentPage.bIconHover=false;
                            currentPage.bIconSelected = false;
                            //equip or add?
                            if(bGunWasEquipped)
                            {
                                //equip
                                currentCharacter->EquipItem(itemManager->GetItem(ItemID::LoadedGunLead));
                            }
                            else
                            {
                                //add
                                currentCharacter->AddToInventory(itemManager->GetItem(ItemID::LoadedGunLead));
                            }


                            RebuildInventory();
                            currentCharacter->UpdateCurrentStats();

                            break;

                    }
                }


                return;
            }
        }


        //iterate over icons
        for(InventoryIcon &icon : currentPage.icons)
        {
            if(mouseX >= icon.position.x && mouseX < (icon.position.x + icon.position.w) &&
               mouseY >= icon.position.y && mouseY < (icon.position.y + icon.position.h) &&
               icon.active && !currentPage.bIconSelected) //mouse in icon, icon has meaning and not clicked
            {

                currentPage.MouseOverIcon=&icon;
                currentPage.bIconHover=true;
                currentPage.bIconSelected = true;
                return;

            }
            else
            {
                currentPage.MouseOverIcon = nullptr;
                currentPage.bIconHover=false;
                currentPage.bIconSelected = false;

            }
        }
    }



};








#endif //SDL_BASE_INVENTORY_COMPONENTS_H
