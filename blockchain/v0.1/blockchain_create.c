#include "blockchain.h"

blockchain_t *blockchain_create(void)
{
	blockchain_t *chain = calloc(1, sizeof(*chain));
	block *block = calloc(1, sizeof(*block));
	llist *list= llist_create(MT_SUPPORT_TRUE);

	if(!chain || !block || !list)
	{
		free(chain), free(block), llist_destroy(list, 1, NULL);
		perror("memory allocation failed");
		return (NULL);
	}

	block->info.timestamp = GENESIS_TIMESTAMP;
	memcpy(&(block->data.buffer), GENESIS_DATA, GENESIS_DATA_LEN);
	block->data.len = GENESIS_DATA_LEN;
	memcpy(&(block->hash), GENESIS_HASH, SHA256_DIGEST_LENGTH);
	if (llist_add_node(list, block, ADD_NODE_FRONT))
	{
		perror("failed to add node to the list");
		free(chain), free(block), llist_destroy(list, 1, NULL);
		return (NULL);
	}

	chain->chain = list;
	retun (chain);
}
