<template>
    <div style="text-align: center;">
      <h3 class="control-heading">Tank Fill Selection</h3>
      <button :class="{ 'control-btn-green': status.tankSelect === 'small', 'control-btn': status.tankSelect === 'none' || 'large' }" @click="selectSmall">
        small
      </button>
      <button :class="{ 'control-btn-green': status.tankSelect === 'large', 'control-btn': status.tankSelect === 'none' || 'small' }" @click="selectLarge">
        large
      </button>
      <button :class="{ 'control-btn-green': status.tankSelect === 'none', 'control-btn': status.tankSelect === 'small' || 'large' }" @click="selectNone">
        drain
      </button>
      <div v-if="error" class="error-message">
      {{ error }}
      </div>
    </div>
  </template>
  
  <script>
  const API_URI = '/sss/api';
  import io from 'socket.io-client';
  
  export default {
    data() {
        return {
            status: {},
            error: null, // Add error property
        }
    },
    mounted() {
        this.fetchStatus();

        const socket = io();
        socket.on('status_update_available', () => {
            this.fetchStatus();
        });
    },
    methods: {
      async selectSmall() {
        try {
          await fetch(`${API_URI}/control/tank`, {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ select: 'small' }),
          });
        } catch (error) {
          console.error('Error:', error);
        }
      },
      async selectLarge() {
        try {
          await fetch(`${API_URI}/control/tank`, {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ select: 'large' }),
          });
        } catch (error) {
          console.error('Error:', error);
        }
      },
      async selectNone() {
        try {
          await fetch(`${API_URI}/control/tank`, {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ select: 'none' }),
          });
        } catch (error) {
          console.error('Error:', error);
        }
      },
      async fetchStatus() {
        try {
            const response = await fetch(`${API_URI}/status`);
            if (response.ok) {
                this.status = await response.json();
                this.error = null; // Reset error on successful fetch
            } else {
                console.error('Failed to get status');
                this.error = 'Failed to fetch status. Please try again later.';
            }
        } catch (error) {
            console.error('Error fetching status:', error);
            this.error = 'Error fetching status. Please check your network connection.';

        }
      },
    },
  };
  </script>

  