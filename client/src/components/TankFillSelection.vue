<template>
    <div>
      <h3>Tank Fill Selection</h3>
      <button :class="{ 'control-btn-green': status.tankSelect === 'small', 'control-btn': status.tankSelect === 'none' || 'large' }" @click="selectSmall">
        small
      </button>
      <button :class="{ 'control-btn-green': status.tankSelect === 'large', 'control-btn': status.tankSelect === 'none' || 'small' }" @click="selectLarge">
        large
      </button>
      <button :class="{ 'control-btn-green': status.tankSelect === 'none', 'control-btn': status.tankSelect === 'small' || 'large' }" @click="selectNone">
        drain
      </button>
    </div>
  </template>
  
  <script>
  const API_URI = 'http://localhost:3000/sss/api';
  import io from 'socket.io-client';
  
  export default {
    data() {
        return {
            status: {},
        }
    },
    mounted() {
        this.fetchStatus();

        const socket = io('http://localhost:3000');
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
            const response = await fetch('http://localhost:3000/sss/api/status');
            if (response.ok) {
                this.status = await response.json();
            } else {
                console.error('Failed to get status');
            }
        } catch (error) {
            console.error('Error fetching status:', error);
        }
      },
    },
  };
  </script>
  
  <style scoped>
  /* Your CSS here */
  </style>
  