---
name: Botanical Veterinary & Care
colors:
  surface: '#f9faf8'
  surface-dim: '#d9dad8'
  surface-bright: '#f9faf8'
  surface-container-lowest: '#ffffff'
  surface-container-low: '#f3f4f2'
  surface-container: '#edeeec'
  surface-container-high: '#e7e8e6'
  surface-container-highest: '#e1e3e1'
  on-surface: '#191c1b'
  on-surface-variant: '#414844'
  inverse-surface: '#2e3130'
  inverse-on-surface: '#f0f1ef'
  outline: '#717974'
  outline-variant: '#c1c8c3'
  surface-tint: '#436557'
  primary: '#002218'
  on-primary: '#ffffff'
  primary-container: '#16382c'
  on-primary-container: '#7ea292'
  inverse-primary: '#aacfbe'
  secondary: '#8d4f00'
  on-secondary: '#ffffff'
  secondary-container: '#ff9c2e'
  on-secondary-container: '#693a00'
  tertiary: '#002217'
  on-tertiary: '#ffffff'
  tertiary-container: '#003a29'
  on-tertiary-container: '#64a78b'
  error: '#ba1a1a'
  on-error: '#ffffff'
  error-container: '#ffdad6'
  on-error-container: '#93000a'
  primary-fixed: '#c5ebd9'
  primary-fixed-dim: '#aacfbe'
  on-primary-fixed: '#002116'
  on-primary-fixed-variant: '#2c4d40'
  secondary-fixed: '#ffdcc0'
  secondary-fixed-dim: '#ffb875'
  on-secondary-fixed: '#2d1600'
  on-secondary-fixed-variant: '#6b3b00'
  tertiary-fixed: '#acf1d1'
  tertiary-fixed-dim: '#90d5b6'
  on-tertiary-fixed: '#002115'
  on-tertiary-fixed-variant: '#00513a'
  background: '#f9faf8'
  on-background: '#191c1b'
  surface-variant: '#e1e3e1'
typography:
  display-lg:
    fontFamily: Manrope
    fontSize: 48px
    fontWeight: '800'
    lineHeight: 56px
    letterSpacing: -0.02em
  display-lg-mobile:
    fontFamily: Manrope
    fontSize: 32px
    fontWeight: '800'
    lineHeight: 40px
    letterSpacing: -0.015em
  headline-lg:
    fontFamily: Manrope
    fontSize: 32px
    fontWeight: '700'
    lineHeight: 40px
    letterSpacing: -0.015em
  headline-lg-mobile:
    fontFamily: Manrope
    fontSize: 26px
    fontWeight: '700'
    lineHeight: 34px
    letterSpacing: -0.01em
  headline-md:
    fontFamily: Manrope
    fontSize: 24px
    fontWeight: '600'
    lineHeight: 32px
    letterSpacing: -0.01em
  headline-sm:
    fontFamily: Manrope
    fontSize: 20px
    fontWeight: '600'
    lineHeight: 28px
    letterSpacing: -0.005em
  title-lg:
    fontFamily: Manrope
    fontSize: 18px
    fontWeight: '600'
    lineHeight: 26px
  body-lg:
    fontFamily: Inter
    fontSize: 16px
    fontWeight: '400'
    lineHeight: 26px
  body-md:
    fontFamily: Inter
    fontSize: 14px
    fontWeight: '400'
    lineHeight: 22px
  body-sm:
    fontFamily: Inter
    fontSize: 12px
    fontWeight: '400'
    lineHeight: 18px
  label-lg:
    fontFamily: Inter
    fontSize: 14px
    fontWeight: '600'
    lineHeight: 20px
    letterSpacing: 0.01em
  label-md:
    fontFamily: Inter
    fontSize: 12px
    fontWeight: '600'
    lineHeight: 16px
    letterSpacing: 0.02em
  label-sm:
    fontFamily: Inter
    fontSize: 11px
    fontWeight: '500'
    lineHeight: 14px
    letterSpacing: 0.03em
rounded:
  sm: 0.125rem
  DEFAULT: 0.25rem
  md: 0.375rem
  lg: 0.5rem
  xl: 0.75rem
  full: 9999px
spacing:
  gutter: 1.5rem
  gutter-sm: 1rem
  margin: 2rem
  margin-sm: 1rem
  space-xs: 0.25rem
  space-sm: 0.5rem
  space-md: 1rem
  space-lg: 1.5rem
  space-xl: 2.5rem
  space-2xl: 4rem
---

## Brand & Style

This design system serves a modern veterinary clinical platform and pet guardian portal. It bridges clinical rigor and compassionate hospitality: veterinary medicine demands utmost clarity, precision, and diagnostic composure, while pet care requires warmth, comfort, and approachable reassurance.

The visual style blends **Modern Organic Minimalism** with **Editorial Clinical Elegance**. Deep botanical forest green anchors medical authority, organic health, and stability. Crisp off-white surfaces provide high legibility and cleanliness, while vibrant marigold and amber accents introduce energetic warmth, directional clarity, and joyful pet-centric cues. Subtly rounded corners, organic backdrop shapes, and refined typography establish a calm, trusted medical ecosystem for both veterinary specialists and loving pet owners.

## Colors

The color architecture is built around natural serenity, clinical authority, and warm navigational guidance:

- **Primary (`#16382C`)**: Deep botanical spruce. Functions as the foundational tone for high-authority elements, primary brand anchors, header bars, deep hero backgrounds, high-contrast headings, and dominant buttons.
- **Secondary (`#F39223`)**: Vibrant warm amber-tangerine. Reserved for high-priority interactive calls to action, urgent booking buttons, medical status alerts, attention tags, and warm focal points.
- **Tertiary (`#3A7D63`)**: Soft sage green. Deployed for subtle background sectioning, active tab indicators, medical milestone tracking, and secondary badges.
- **Neutral Surface (`#F9FAF8`)**: Crisp botanical off-white. Emits hygienic warmth without the harshness of pure `#FFFFFF`, minimizing eye strain in clinical dashboard environments while keeping cards crisp.
- **Text & Borders**: High-emphasis copy defaults to deep `#16382C` or `#18221D`, secondary copy utilizes `#516058`, and structural card dividers leverage a soft natural tint `#E3E8E3`.

## Typography

Typography balances structural balance with human warmth:

- **Headlines (`Manrope`)**: Geometric sans-serif with subtle humanist curvature. The slightly open counters convey approachability and veterinary companionship while maintaining structural strength in titles and modal headers.
- **Body & Data (`Inter`)**: Utilitarian, highly legible workhorse optimized for multi-screen readability. Essential for veterinary dosage instructions, clinical timelines, diagnostic values, and dense pet record tables.
- **Hierarchy Rules**: 
  - Never set headings in pure saturated blacks; use the deep botanical primary `#16382C` to preserve organic harmony.
  - On deep green section panels, titles invert to pure `#FFFFFF` with secondary notes styled in an 85% translucent mist (`rgba(255, 255, 255, 0.85)`).

## Layout & Spacing

This design system uses a responsive 12-column grid layout across desktop and tablet, collapsing to a structured 4-column fluid system on mobile screens:

- **Desktop (1024px+)**: Max content container constrained to `1280px` centered, utilizing `gutter: 1.5rem` and outer canvas `margin: 2rem`. Allows card grids (pet profiles, service listings, appointment matrices) to cleanly span 3, 4, or 6 columns.
- **Tablet (768px - 1023px)**: 8-column layout with `gutter: 1rem` and `margin: 1.5rem`. Pet biometric summaries and doctor schedules reflow from 3 across to 2 across.
- **Mobile (<768px)**: 4-column single-flow layout with `margin-sm: 1rem` and `gutter-sm: 1rem`. Cards and interactive lists take full width.

Organic page sections alternate between light backgrounds (`#F9FAF8`) and continuous deep green botanical panels (`#16382C`) with organic undulating transitions or generous vertical breathing room (`space-2xl`).

## Elevation & Depth

Visual depth is achieved through **ambient organic shadows** combined with **subtle structural borders**, rejecting stark harsh drops in favor of soft clinical layering:

- **Surface Base (Level 0)**: Flat `#F9FAF8` canvas or deep `#16382C` background bands.
- **Card Tier 1 (Resting)**: White `#FFFFFF` card surface, soft 1px border (`#E5EBE7`), overlaid with an ambient shadow: `0 4px 16px -4px rgba(22, 56, 44, 0.06), 0 2px 6px -2px rgba(22, 56, 44, 0.04)`.
- **Interactive Hover (Level 2)**: Elevation shifts upward on hover with subtle transform `-2px` and expanded shadow: `0 12px 24px -6px rgba(22, 56, 44, 0.10), 0 4px 8px -2px rgba(22, 56, 44, 0.04)`.
- **Floating Overlays & Modals (Level 3)**: Clinical dialogues and diagnostic lightboxes float with `0 20px 40px -10px rgba(22, 56, 44, 0.18)` against a 40% botanical backdrop scrim (`rgba(22, 56, 44, 0.4)`).
- **Embedded Badges & Secondary Panels**: Tonal layering without shadows, using soft tinted fills such as `rgba(22, 56, 44, 0.04)` or `#EDF3EE` to group child data cleanly inside parent cards.

## Shapes

With `roundedness: 1` (Soft), the design system establishes a clinical yet gentle geometry:

- **Base Components**: Inputs, buttons, chips, and small badges maintain a crisp, structured `0.25rem` (4px) to `0.375rem` (6px) corner radius, preserving medical neatness.
- **Cards & Diagnostic Containers (`rounded-lg`)**: Structured at `0.5rem` (8px) corner radius, keeping layouts solid and disciplined.
- **Highlight Panels & Hero Cards (`rounded-xl`)**: Utilize `0.75rem` (12px) to softly frame focal content.
- **Organic Visual Accents**: Asymmetrical organic backdrops (such as circular organic blobs or soft pill frames for pet photographs) are strictly isolated to imagery masks and decorative silhouette badges, contrasting against the disciplined, structured UI cards.

## Components

### Buttons
- **Primary Action (Emergency/Book)**: Background `#F39223`, text `#FFFFFF`, font weight `600`, height `44px`, padding `0 1.25rem`, radius `0.25rem`. Hover shifts to `#DE7F17`.
- **Clinical Primary**: Background `#16382C`, text `#FFFFFF`, hover `#1D4638`.
- **Secondary / Outlined**: Border `1.5px solid #16382C`, transparent background, text `#16382C`, hover background `rgba(22, 56, 44, 0.05)`.
- **Subtle / Ghost**: Transparent background, text `#3A7D63`, hover background `#EDF3EE`.

### Cards & Modules
- **Pet Profile Card**: White `#FFFFFF` container with `rounded-lg` (8px), 1px border `#E5EBE7`, padding `1.25rem`. Houses circular pet avatar (48px) with status indicator (e.g., green dot for vaccinated), pet breed, age, and quick clinical actions.
- **Medical Metric Card**: Compact card with tinted tertiary background (`rgba(58, 125, 99, 0.08)`), containing metric value in `Manrope` bold and label in `Inter` uppercase label-sm.

### Form Inputs & Selectors
- **Text Inputs**: Height `44px`, background `#FFFFFF`, border `1px solid #D6DFD9`, radius `0.25rem`, padding `0 0.875rem`, text `Inter 14px`. Focus state shows border `1.5px solid #16382C` with an ambient glow `0 0 0 3px rgba(22, 56, 44, 0.12)`.
- **Validation**: Error states utilize `#D32F2F` border and helper text; verified states utilize `#3A7D63`.

### Chips & Badges
- **Status Badges**: Padding `4px 10px`, radius `0.25rem`, font `label-sm`.
  - *Confirmed / Healthy*: Background `#E8F5EF`, text `#1B6346`.
  - *Pending / Urgent*: Background `#FEF3E6`, text `#B85C00`.
  - *Clinical Species Tag*: Background `#EDF2EE`, text `#16382C`.

### Lists & Timelines
- **Medical Records List**: Alternating rows with clean dividing borders (`1px solid #EBEFEB`), interactive hover fill `#F4F7F5`, date pill in tertiary color, and status chevron icon on trailing edge.

### Checkboxes & Radios
- Size `18px x 18px`, border `1.5px solid #94A69C`, radius `3px` (radios `50%`). Checked state fills with `#16382C` displaying a crisp white micro checkmark.