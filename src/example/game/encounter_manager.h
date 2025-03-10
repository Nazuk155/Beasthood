#pragma once
#include "../global.hpp"
#include "encounter.h"
#include "skillCheckEngine.h"
#include "item_manager.h"
#include "quests.h"
#include "map.h"



// EncounterManager class
class EncounterManager {
public:

    ItemManager* iManager;
   // SDL_Point SzeneOptionStatus;

    // Add a new encounter
    void addEncounter(EncounterID id, const Encounter& encounter) {
        if (encounter.validate()) {
            encounters[id] = encounter;
        } else {
            throw std::runtime_error("Invalid encounter: Scenes must have at least one option.");
        }
    }

    // Get an encounter by ID
    const Encounter* getEncounter(EncounterID id) const {
        auto it = encounters.find(id);
        if (it != encounters.end()) {
            return &it->second;
        }
        return nullptr;
    }
    Encounter* GetEncounter(EncounterID id) {
        auto it = encounters.find(id);
        return (it != encounters.end()) ? &it->second : nullptr;
    }



    // Remove an encounter by ID
    void removeEncounter(EncounterID id) {
        encounters.erase(id);
    }

    // Check if an encounter exists
    bool hasEncounter(EncounterID id) const {
        return encounters.find(id) != encounters.end();
    }



/*
    bool ResolveEncounter(Encounter &encounter,int szene,int input,SkillChallengeEngine ske, Character & currentCharacter) {
        switch (encounter.currentDialoguePhase) {
            case DialoguePhase::Scene:
                input = input - 1;

                //new idea








                if (!encounter.scenes[szene].options[input - 1].isSkillCheck) {
                    //if Jump Target is escape value TODO define further behavior, construct Combat encounter encoding and Jump
                    if (encounter.scenes[szene].options[input - 1].jumpTargetSuccess ==
                        255) {
                        return true;
                    } else {
                        szene = encounter.scenes[szene].options[input - 1].jumpTargetSuccess;
                    }
                } else {


                    //ske.bIsActive=true; todo put flag in other place
                    ske.setDifficulty(
                            encounter.scenes[szene].options[input - 1].difficulty);
                    ske.setModifier(0);
                    ske.setSkill(encounter.scenes[szene].options[input - 1].skill);


                    if (ske.checkSkill()) {//Skillcheck Passed
                        iterateOverOutcomes(encounter.scenes[szene].options[input].rewardItemIDs,
                                encounter.scenes[szene].options[input].successOutcomes,currentCharacter);
                        szene = encounter.scenes[szene].options[input].jumpTargetSuccess;
                        //bNeedInput = false;

                    } else {
                        //Not Passed TODO
                        if (currentCharacter.GetFatePoints() > 0) { // can spend will

                        } else {
                            //  bNeedInput = false;
                            iterateOverOutcomes(
                                    encounter.scenes[szene].options[input].failureOutcomes);
                            szene = encounter.scenes[szene].options[input].jumpTargetFail;
                        }


                    }
                    encounter.currentDialoguePhase = DialoguePhase::DieRoll;
                }


                input = -1;

                break;
            case DialoguePhase::DieRoll: // misnomer
                //???
                if (bNeedInput) {
                    //if any WP avalkable
                    switch (CurrentInput) {
                        case 1: // todo move to reroll phase?
                            character1->SpendFate();
                            dialoguePhase = DialoguePhase::FateReroll;
                            bNeedInput = false;
                            if (ske.addFateDice()) //todo seems broken
                            {
                                //Passed after Fateroll
                                iterateOverOutcomes(
                                        CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].SuccessOutcomes);
                                CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetSuccess;
                            } else {
                                fmt::println("Debug fate fail!");
                                iterateOverOutcomes(
                                        CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].FailureOutcomes);
                                CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetFail;
                            }

                            break;
                        case 2:
                            //Choose to fail/not roll
                            iterateOverOutcomes(
                                    CurrentEncounter.Scenes[CurrentScene].Options[CurrentInput - 1].FailureOutcomes);
                            CurrentScene = CurrentEncounter.Scenes[CurrentScene].Options[ChosenOption].JumpTargetFail;

                            dialoguePhase = DialoguePhase::Scene;
                            break;
                        default:;


                    }
                    CurrentInput = -1;

                } else {
                    dialoguePhase = DialoguePhase::Scene;
                    bNeedInput = true;
                }


                break;
            case DialoguePhase::FateReroll:


                dialoguePhase = DialoguePhase::Scene;
                CurrentInput = -1;
                bNeedInput = true;
                break;
        }
    }
*/

///refactored this so it returns a ExecuteFlag which we use in a switch to resolve the outcome in beasthoodstate
///handle all future added outcomes outside for easier access to functionality - Max
Vector<ExecuteFlags> iterateOverOutcomes(const Vector<ItemID>& rewards, const std::vector<std::tuple<ExecuteFlags, int>> &outcomes, Character &currentCharacter, QuestLog& questlog) const {
    Vector<ExecuteFlags> results;
    for (std::tuple<ExecuteFlags, int> outcome: outcomes) {

        switch (get<0>(outcome)) {
            case ExecuteFlags::Wound:
                fmt::print("Debug- Injury");
                currentCharacter.AdjustStamina(-get<1>(outcome));
                results.push_back(ExecuteFlags::Wound);
                break;
            case ExecuteFlags::GainItem:
                for(auto e : rewards) {
                    fmt::println("Adding item");
                    currentCharacter.AddToInventory(iManager->GetItem(e));
                }

                results.push_back(ExecuteFlags::GainItem);
                break;
            case ExecuteFlags::LoseItem:
                for(auto e : rewards) {
                    fmt::println("Losing item {}",iManager->GetItem(e)->GetName());
                    currentCharacter.RemoveFromInventory(iManager->GetItem(e)->GetItemID());
                }
                //TODO Ressources
                results.push_back(ExecuteFlags::GainItem);
                break;
            case ExecuteFlags::UnloadSilverBullet:
                results.push_back(ExecuteFlags::UnloadSilverBullet);break;
            case ExecuteFlags::UnloadLeadBullet:
                results.push_back(ExecuteFlags::UnloadLeadBullet);break;
            case ExecuteFlags::GainBulletLead:

                if (currentCharacter.leadBulletCount == 0)
                {
                    currentCharacter.AddToInventory(iManager->GetItem(ItemID::BulletLead));

                }
                fmt::println("Gaining {} bullets",get<1>(outcome));
                currentCharacter.leadBulletCount += get<1>(outcome);
                break;
            case ExecuteFlags::Heal:
                currentCharacter.AdjustStamina(get<1>(outcome));
                results.push_back(ExecuteFlags::Heal);break;
            case ExecuteFlags::SanityLoss:
                currentCharacter.AdjustSanity(-get<1>(outcome)); //todo fix this mess/warning
                results.push_back(ExecuteFlags::SanityLoss);
                break;
            case ExecuteFlags::RegainSan:
                currentCharacter.AdjustSanity(get<1>(outcome));
                results.push_back(ExecuteFlags::RegainSan);break;

            case ExecuteFlags::StartQuest:
                if(!questlog.addQuest(get<1>(outcome)))
                {
                    fmt::println("Failed to add quest {}", get<1>(outcome));
                }else
                {
                    fmt::println("started quest:",get<1>(outcome));
                }
                results.push_back(ExecuteFlags::StartQuest);break;

            case ExecuteFlags::AdvanceQuestStage:
            {
                int questId = get<1>(outcome)/1000;
                int stageID = get<1>(outcome)%1000;
                for(Quest& q: questlog.activeQuests)
                {
                    if(q.questID == questId)
                    {
                        if(q.currentQuestStage != stageID)
                        {


                            for(std::pair<int, String>& Stage: q.questStages)
                            {
                                if(Stage.first==stageID)
                                {
                                    fmt::println("Quest {} progressed from {} to {}", questId, q.currentQuestStage,stageID);
                                    q.currentQuestStage=stageID;


                                }
                            }
                        }

                    }
                }

            } results.push_back(ExecuteFlags::AdvanceQuestStage)
            ;break;
            case ExecuteFlags::StartCombat:

                results.push_back(ExecuteFlags::StartCombat)
                ;break;

            case ExecuteFlags::FinishedCombatWIN:

                results.push_back(ExecuteFlags::FinishedCombatWIN)
                ;break;
            case ExecuteFlags::FinishedCombatLOSS:

                results.push_back(ExecuteFlags::FinishedCombatLOSS);
                break;
            case ExecuteFlags::SpawnMonster:

                results.push_back(ExecuteFlags::SpawnMonster);
                break;

            case ExecuteFlags::RemoveEncounter:

                results.push_back(ExecuteFlags::RemoveEncounter);
                break;
            case ExecuteFlags::RecoverFate:
                results.push_back(ExecuteFlags::RecoverFate);
                break;
        }
    }
        return results;
    }



private:
    std::unordered_map<EncounterID, Encounter> encounters;
};