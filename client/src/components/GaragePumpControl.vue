<template>
  <div style="text-align: center;">
    <h3 class="control-heading">Garage Pump Control</h3>
    <button  :class="{ 'control-btn-green': status.garagePump === 'on', 'control-btn-red': status.garagePump === 'off' }" @click="togglePump">
      {{ status.garagePump === 'on' ? 'Turn OFF Garage Pump' : 'Turn ON Garage Pump' }}
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
