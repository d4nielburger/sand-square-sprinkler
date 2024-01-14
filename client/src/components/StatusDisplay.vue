<template>
    <div>
        <h2>Status</h2>
        <pre>{{ status }}</pre>
    </div>
</template>

<script>
import io from 'socket.io-client';

export default {
    data() {
        return {
            status: {},
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
        async fetchStatus() {
            try {
                const response = await fetch('/sss/api/status');
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
 /* ToDo */
</style>