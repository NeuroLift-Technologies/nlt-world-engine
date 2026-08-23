// World Engine HUD — HTML overlay showing tick count, avatar stats, event log.
//
// Ported from the React-based HUD in the original prototype.
// Now a lightweight vanilla TS overlay.

import type { WorldState, AvatarState } from './simulation';

// ─── HUD Controller ──────────────────────────────────────────────
export class HUD {
  private hudTop: HTMLElement | null;
  private pairInfo: HTMLElement | null;
  private eventsDiv: HTMLElement | null;
  private selectedId: string | null = null;

  constructor() {
    this.hudTop = document.getElementById('hud-top');
    this.pairInfo = document.getElementById('pair-info');
    this.eventsDiv = document.getElementById('events');
  }

  setSelected(id: string | null): void {
    this.selectedId = id;
  }

  getSelected(): string | null {
    return this.selectedId;
  }

  // ─── Render full HUD ────────────────────────────────────────────
  render(world: WorldState): void {
    this.renderTop(world);
    this.renderPairInfo(world);
    this.renderEvents(world);
  }

  private renderTop(world: WorldState): void {
    if (!this.hudTop) return;
    this.hudTop.innerHTML = '';

    const tickChip = document.createElement('span');
    tickChip.className = 'hud-chip';
    tickChip.textContent = `Tick: ${world.tickCount}`;
    this.hudTop.appendChild(tickChip);

    const timeChip = document.createElement('span');
    timeChip.className = 'hud-chip';
    const hours = Math.floor(world.simTime / 60) % 24;
    const mins = Math.floor(world.simTime) % 60;
    timeChip.textContent = `Time: ${String(hours).padStart(2, '0')}:${String(mins).padStart(2, '0')}`;
    this.hudTop.appendChild(timeChip);

    const simsChip = document.createElement('span');
    simsChip.className = 'hud-chip';
    simsChip.textContent = `Avatars: ${world.avatars.length}`;
    this.hudTop.appendChild(simsChip);
  }

  private renderPairInfo(world: WorldState): void {
    if (!this.pairInfo) return;
    this.pairInfo.innerHTML = '';

    // Show selected avatar in detail, or first 6 avatars
    const avatars = this.selectedId
      ? world.avatars.filter((a) => a.id === this.selectedId)
      : world.avatars.slice(0, 6);

    for (const av of avatars) {
      const chip = this.buildAvatarChip(av);
      this.pairInfo.appendChild(chip);
    }
  }

  private buildAvatarChip(av: AvatarState): HTMLElement {
    const chip = document.createElement('div');
    chip.className = 'pair-chip';
    chip.style.setProperty('--c', `hsl(${av.hue}, 70%, 60%)`);

    const stateIcon = this.stateIcon(av.state);

    chip.innerHTML = `
      <strong>${av.name}</strong> ${stateIcon}<br>
      <span style="opacity:0.8;font-size:11px">
        state: ${av.state} | focus: ${(av.focus * 100).toFixed(0)}% |
        stress: ${(av.stress * 100).toFixed(0)}% | room: ${av.room}
      </span>
    `;

    chip.addEventListener('click', () => {
      this.selectedId = av.id;
    });

    return chip;
  }

  private renderEvents(world: WorldState): void {
    if (!this.eventsDiv) return;
    this.eventsDiv.innerHTML = '';

    const header = document.createElement('div');
    header.style.fontWeight = 'bold';
    header.style.marginBottom = '6px';
    header.textContent = 'Recent Events';
    this.eventsDiv.appendChild(header);

    const events = world.events.slice(0, 8);
    for (const evt of events) {
      const row = document.createElement('div');
      row.className = 'event-row';
      const hue = evt.avatarHue;
      row.innerHTML = `
        <span style="color:hsl(${hue},70%,65%)">${evt.avatarName}</span>:
        <span style="opacity:0.9">${evt.text}</span>
      `;
      this.eventsDiv.appendChild(row);
    }
  }

  private stateIcon(state: string): string {
    switch (state) {
      case 'drifting': return '…';
      case 'hyperfocus': return '◉';
      case 'overwhelmed': return '!';
      case 'coached': return '✦';
      case 'working': return '▸';
      case 'idle': return '○';
      default: return '';
    }
  }
}