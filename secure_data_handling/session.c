#include <stdlib.h>
#include <string.h>
#include "session.h"

/**
 * session_create - creates a self-contained session
 * @id: the session id (duplicated, so the session owns its own copy)
 * @uid: the user id
 * @data: the data buffer to copy (may be NULL if data_len is 0)
 * @data_len: the length of the data buffer
 *
 * Return: pointer to the new session, or NULL on failure
 */
session_t *session_create(const char *id, unsigned int uid,
		const unsigned char *data, size_t data_len)
{
	session_t *s;

	if (!id)
		return (NULL);

	s = (session_t *)malloc(sizeof(*s));
	if (!s)
		return (NULL);

	s->id = strdup(id);
	if (!s->id) {
		free(s);
		return (NULL);
	}

	s->uid = uid;

	if (data_len > 0) {
		s->data = (unsigned char *)malloc(data_len);
		if (!s->data) {
			free(s->id);
			free(s);
			return (NULL);
		}
		memcpy(s->data, data, data_len);
		s->data_len = data_len;
	} else {
		s->data = NULL;
		s->data_len = 0;
	}

	return (s);
}

/**
 * session_set_data - safely updates the session's data buffer
 * @s: the session to update
 * @data: the new data buffer to copy
 * @data_len: the length of the new data (0 clears the buffer)
 *
 * Return: 1 on success, 0 on failure
 */
int session_set_data(session_t *s, const unsigned char *data, size_t data_len)
{
	unsigned char *tmp;

	if (!s)
		return (0);

	if (data_len == 0) {
		free(s->data);
		s->data = NULL;
		s->data_len = 0;
		return (1);
	}

	tmp = (unsigned char *)realloc(s->data, data_len);
	if (tmp == NULL)
		return (0);

	s->data = tmp;
	memcpy(s->data, data, data_len);
	s->data_len = data_len;
	return (1);
}

/**
 * session_destroy - frees a session and all memory it owns
 * @s: the session to destroy
 */
void session_destroy(session_t *s)
{
	if (!s)
		return;

	free(s->id);
	free(s->data);
	free(s);
}
