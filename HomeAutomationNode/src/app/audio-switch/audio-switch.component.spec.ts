import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { AudioSwitchComponent } from './audio-switch.component';

describe('AudioSwitchComponent', () => {
  let component: AudioSwitchComponent;
  let fixture: ComponentFixture<AudioSwitchComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ AudioSwitchComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(AudioSwitchComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
