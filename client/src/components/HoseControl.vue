<template>
    <div style="text-align: center;">
      <h3 class="control-heading">Hose Control</h3>
      <button :class="{ 'control-btn-green': status.hose === 'on', 'control-btn-red': status.hose === 'off' }" @click="toggleHose">
        {{ status.hose === 'on' ? 'Turn OFF Hose' : 'Turn ON Hose' }}
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
      async toggleHose() {
        if (this.status.hose == 'on') {
          try {
            await fetch(`${API_URI}/control/hose`, {
              method: 'POST',
              headers: {
                'Content-Type': 'application/json',
              },
              body: JSON.stringify({ state: 'off' }),
            });
          } catch (error) {
            console.error('Error:', error);
          }        
        } else {
          try {
            await fetch(`${API_URI}/control/hose`, {
              method: 'POST',
              headers: {
                'Content-Type': 'application/json',
              },
              body: JSON.stringify({ state: 'on' }),
            });
          } catch (error) {
            console.error('Error:', error);
          }        
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
  