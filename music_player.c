
#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t *create_playlist() // return a newly created doubly linked list
{
    // DO NOT MODIFY!!!
    playlist_t *playlist = (playlist_t *)malloc(sizeof(playlist_t));
    playlist->list = create_list();
    playlist->num_songs = 0;
    playlist->last_song = NULL;
    return playlist;
}

void delete_playlist(playlist_t *playlist) // delete the playlist
{
    // DO NOT MODIFY!!!
    delete_list(playlist->list);
    free(playlist);
}

music_queue_t *create_music_queue() // return a newly created queue
{
    // DO NOT MODIFY!!!
    return create_queue();
}

void clear_music_queue(music_queue_t *q) // clear the queue q
{
    // DO NOT MODIFY!!!
    delete_queue(q);
}

void add_song(playlist_t *playlist, int song_id, int where) // TODO: add a song id to the end of the playlist
{
    if (where == -1)
    {
        insert_front(playlist->list, song_id);
    }
    else if (where == -2)
    {
        insert_back(playlist->list, song_id);
    }
    else if (where > -1)
    {
        insert_after(playlist->list, song_id, where);
    }
    playlist->num_songs = playlist->list->size;
}

void delete_song(playlist_t *playlist, int song_id) // TODO: remove song id from the playlist
{
    if (!is_empty(playlist->list))
    {
        delete_node(playlist->list, song_id);
        playlist->num_songs--;
    }
}

song_t *search_song(playlist_t *playlist, int song_id) // TODO: return a pointer to the node where the song id is present in the playlist
{
    song_t *ans;
    if (!is_empty(playlist->list))
    {
        ans = search(playlist->list, song_id);
    }
    return ans;
}

void search_and_play(playlist_t *playlist, int song_id) // TODO: play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
    if (!is_empty(playlist->list))
    {
        song_t *temp;
        temp = search_song(playlist, song_id);
        if (temp != NULL)
        {
            play_song(temp->data);
            playlist->last_song = temp;
        }
        else
        {
            printf("Searched song not found \n");
        }
    }
}

void play_next(playlist_t *playlist, music_queue_t *q) // TODO: play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{

    if (playlist->list == NULL)
        return; 

    if (q!= NULL && !empty(q)) 
    {
        play_from_queue(q);
    }
    else 
    {
        
        if (playlist->last_song == NULL)
        {
            play_song(playlist->list->head->data); 
            playlist->last_song = playlist->list->head;
            return;
        }
        else
        {
            if (playlist->last_song->data == playlist->list->tail->data) 
            {
                play_song(playlist->list->head->data);
                playlist->last_song = NULL;
               
            }
            else
            {
                song_t *nextSong = playlist->last_song->next;
                if (nextSong->data == playlist->list->tail->data)
                {
                    play_song(nextSong->data);
                    playlist->last_song = NULL;
                    
                }
                else
                {
                    play_song(playlist->last_song->next->data);
                    playlist->last_song = playlist->last_song->next;
                    
                }
            }
        }
    }
}

void play_previous(playlist_t *playlist) // TODO: play the previous song from the linked list
{
    if (playlist->list == NULL) 
        return;
   

  
    if(playlist->last_song == NULL)
    {
        play_song(playlist->list->tail->data);
        playlist->last_song = playlist->list->tail;
        return;
    }
    else
    {
        song_t *prevSong = playlist->last_song->prev;
        if(prevSong == NULL)
        {
            play_song(playlist->list->tail->data);
            playlist->last_song = playlist->list->tail;
            return;
        }
        if (prevSong->data == playlist->list->head->data)
        {
        
            
            play_song(prevSong->data);
            playlist->last_song =NULL;
            
        }
        else
        {
            play_song(prevSong->data);
            playlist->last_song = prevSong;
        }
       
    }
    
   
}

void play_from_queue(music_queue_t *q) // TODO: play a song from the queue
{
    int song_id;
    if (!empty(q))
    {
        song_id = dequeue(q);
        play_song(song_id);
    }
}

void insert_to_queue(music_queue_t *q, int song_id) // TODO: insert a song id to the queue
{
    if (!empty(q))
    {
        enqueue(q, song_id);
    }
}

void reverse(playlist_t *playlist) // TODO: reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{
    song_t *current, *temp;
    current = playlist->list->head;
    while (current != NULL)
    {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }
    temp = playlist->list->head;
    playlist->list->head = playlist->list->tail;
    playlist->list->tail = temp;
}

void k_swap(playlist_t *playlist, int k) // TODO: swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{

    if(k > playlist->list->size) return;
    song_t *source, *destination;
    int index = 1;
    int jumpIndex = 0;
    int temp=0;
    
    source = playlist->list->head;
    for (int i= 0; i < playlist->list->size; i++)
    {
        destination = source;
        jumpIndex = i + k;
       for (int j=i; j< jumpIndex; j++)
        {
            if(destination != NULL )
            {
                 destination = destination->next;
            }
        }
        if(destination !=NULL)
        {

            temp = source->data;
            source->data = destination->data;
            destination->data = temp;
            source = source->next;
        }
        
        
    }

}

void shuffle(playlist_t *playlist, int k) // TODO: perform k_swap and reverse
{
    k_swap(playlist, k);
    reverse(playlist);
}

song_t *debug(playlist_t *playlist) // TODO: if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{
    song_t *pres;
    pres = playlist->list->tail->next;
    if(pres!=NULL)
        return pres;
    else
        return NULL;
    
}

void display_playlist(playlist_t *p) // Displays the playlist
{
    // DO NOT MODIFY!!!
    display_list(p->list);
}

void play_song(int song_id)
{
    // DO NOT MODIFY!!!
    printf("Playing: %d\n", song_id);
}



