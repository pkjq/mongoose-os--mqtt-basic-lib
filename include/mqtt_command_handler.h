/*
 * Copyright (c) 2019 pkjq
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef G4C9CD20A_7B13_4E19_9F49_A393DA374738
#define G4C9CD20A_7B13_4E19_9F49_A393DA374738


namespace mqtt
{
struct ICommands
{
    virtual void OnCmdAnnounce() const = 0;
};


void CreateCommandHandler(const char *command_topic, ICommands &commands);
}


#endif//G4C9CD20A_7B13_4E19_9F49_A393DA374738
