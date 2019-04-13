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

#include <mgos.h>
#include <mgos_mqtt.h>
#include <common/json_utils.h>

#include <mgos_system.h>
#include "mqtt_command_handler.h"

#include <memory>


namespace mqtt
{
namespace
{
void MqttJsonCallback(void *data, const char *name, size_t name_len, const char *path, const struct json_token *tok)
{
    (void)data;
    (void)name;
    (void)name_len;
    (void)path;
    (void)tok;

    auto &commands = *static_cast<ICommands*>(data);

    switch (tok->type)
    {
    case JSON_TYPE_STRING:
    {
        const char *value = tok->ptr;
        const auto len = tok->len;

        if (!strcmp(path, ".do")) // "'payload': { 'do':'announce' }"
        {
            if (!strncmp(value, "announce", len))
                commands.OnCmdAnnounce();
        }
        break;
    }

    default:
        break;
    }
}

void MqttHandlerCallback(struct mg_connection *c, const char *topic, int topic_len, const char *msg, int msg_len, void *data)
{
    (void)c;
    (void)msg;
    (void)msg_len;
    (void)data;

    LOG(LL_INFO, ("Got message on topic %.*s", topic_len, topic));

    json_walk(msg, msg_len, MqttJsonCallback, data);
}
}


///////////////////////////////////////////////////
void CreateCommandHandler(const char *command_topic, ICommands &commands)
{
    mgos_mqtt_sub(command_topic, MqttHandlerCallback, &commands);
}
}