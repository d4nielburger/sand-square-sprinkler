<template>
  <div>
    <h3>Garage Pump Control</h3>
    <button  :class="{ 'control-btn-green': status.garagePump === 'on', 'control-btn-red': status.garagePump === 'off' }" @click="togglePump">
      {{ status.garagePump === 'on' ? 'Turn OFF Garage Pump' : 'Turn ON Garage Pump' }}
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
    async togglePump() {
      if (this.status.garagePump == 'on') {
        try {
          await fetch(`${API_URI}/control/garage-pump`, {
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
          await fetch(`${API_URI}/control/garage-pump`, {
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

<style scoped>
/* Your CSS here */
</style>
