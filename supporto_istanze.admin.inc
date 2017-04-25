<?php
/**
 * @file
 * settings file
 */
 
/**
 * Settings form.
 */
function supporto_istanze_admin_settings_form() {
  $my_nodes = array();
  node_types_rebuild();
  $node_types = node_type_get_types();
  foreach ($node_types as $node_type) {
    $my_nodes[$node_type->type] = $node_type->type;
  }

  $form['supporto_istanze_content1'] = array(
    '#type' => 'fieldset',
    '#title' => 'Tipi di contenuto',
  );
  $form['supporto_istanze_content1']['supporto_istanze_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => 'tipi di contenuto usati per le istanze',
    '#default_value' => variable_get('supporto_istanze_node_types', array('istanze_del_personale' => 'istanze_del_personale')),
    '#options' => $my_nodes,
    '#multiple' => TRUE,
  );
  $form['supporto_istanze_content2'] = array(
    '#type' => 'fieldset',
    '#title' => 'Email della segreteria',
  );
  $form['supporto_istanze_content2']['supporto_istanze_email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#maxlength' => 254,
    '#description' => 'indirizzo e-mail valido',
    '#required' => TRUE,
    '#default_value' => variable_get('supporto_istanze_email', ''),
  );
  $form['supporto_istanze_content2']['supporto_istanze_notification_email'] = array(
    '#type' => 'checkbox',
    '#title' => 'Invia, in modo predefinito, email di istanza evasa alla segreteria',
    '#defaul_value' => variable_get('supporto_istanze_notification_email', FALSE),
    '#attributes' => variable_get('supporto_istanze_notification_email', FALSE) ? array('checked' => 'checked') : NULL,
  );
  $form['supporto_istanze_content3'] = array(
    '#type' => 'fieldset',
    '#title' => 'Testo delle email di notifica',
  );
  $form['supporto_istanze_content3']['supporto_istanze_notification_body'] = array(
    '#type' => 'textarea',
    '#title' => "Notifica all'utente. E' possibile modificare il testo del messaggio utilizzando i riferimenti preceduti da @ come da esempio.",
    '#default_value' => variable_get('supporto_istanze_notification_body', "La sua istanza @istanza, n. @istanza_id del @data, è stata @esito."),
  );
  $form['supporto_istanze_content3']['supporto_istanze_segreteria_subject'] = array(
    '#type' => 'textfield',
    '#title' => "Oggetto email alla segreteria. E' possibile modificare il testo dell'oggetto utilizzando i riferimenti come sopra.",
    '#default_value' => variable_get('supporto_istanze_segreteria_subject', "Notifica istanza evasa - @istanza n. @istanza_serial - @nome"),
  );
  $form['supporto_istanze_content3']['supporto_istanze_segreteria_body'] = array(
    '#type' => 'textarea',
    '#title' => "Email alla segreteria. E' possibile modificare il testo del messaggio utilizzando i riferimenti come sopra.",
    '#default_value' => variable_get('supporto_istanze_segreteria_body', "L'istanza @istanza, n. @istanza_id del @data presentata da @nome, è stata @esito."),
  );
  $form['supporto_istanze_content3']['supporto_istanze_notification_footer'] = array(
    '#type' => 'textarea',
    '#title' => "Saluti e firma. E' possibile modificare il testo del messaggio utilizzando i riferimenti come sopra.",
    '#default_value' => variable_get('supporto_istanze_notification_footer', "Cordiali saluti,\n@operatore (@qualifica_operatore)."),
  );
  $form['supporto_istanze_content4'] = array(
    '#type' => 'fieldset',
    '#title' => 'File di segnatura allegato email',
  );
  $form['supporto_istanze_content4']['supporto_istanze_instance_signature'] = array(
    '#type' => 'checkbox',
    '#title' => 'Segnatura su trasmissione istanza',
    '#defaul_value' => variable_get('supporto_istanze_instance_signature', FALSE),
    '#attributes' => variable_get('supporto_istanze_instance_signature', FALSE) ? array('checked' => 'checked') : NULL,
  );
  $form['supporto_istanze_content4']['supporto_istanze_evaded_signature'] = array(
    '#type' => 'checkbox',
    '#title' => 'Segnatura su istanza evasa',
    '#defaul_value' => variable_get('supporto_istanze_evaded_signature', FALSE),
    '#attributes' => variable_get('supporto_istanze_evaded_signature', FALSE) ? array('checked' => 'checked') : NULL,
  );
  $form['supporto_istanze_content4']['supporto_istanze_email_protocollo'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#description' => 'indirizzo e-mail da filtrare',
    '#default_value' => variable_get('supporto_istanze_email_protocollo', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_nome_scuola'] = array(
    '#type' => 'textfield',
    '#title' => 'Denominazione ufficiale dell\'Istituto',
    '#default_value' => variable_get('supporto_istanze_nome_scuola', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_codice_amm'] = array(
    '#type' => 'textfield',
    '#title' => 'Codice amministrazione',
    '#default_value' => variable_get('supporto_istanze_codice_amm', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_codice_aoo'] = array(
    '#type' => 'textfield',
    '#title' => 'Codice AOO',
    '#default_value' => variable_get('supporto_istanze_codice_aoo', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_toponimo'] = array(
    '#type' => 'textfield',
    '#title' => 'Toponimo (via o piazza etc.)',
    '#default_value' => variable_get('supporto_istanze_toponimo', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_civico'] = array(
    '#type' => 'textfield',
    '#title' => 'Numero civico',
    '#default_value' => variable_get('supporto_istanze_civico', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_cap'] = array(
    '#type' => 'textfield',
    '#title' => 'CAP',
    '#default_value' => variable_get('supporto_istanze_cap', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_comune'] = array(
    '#type' => 'textfield',
    '#title' => 'Comune',
    '#default_value' => variable_get('supporto_istanze_comune', ''),
  );
  $province = array(
    'AG' => 'Agrigento',
    'AL' => 'Alessandria',
    'AN' => 'Ancona',
    'AO' => 'Aosta',
    'AR' => 'Arezzo',
    'AP' => 'Ascoli Piceno',
    'AT' => 'Asti',
    'AV' => 'Avellino',
    'BA' => 'Bari',
    'BT' => 'Barletta-Andria-Trani',
    'BL' => 'Belluno',
    'BN' => 'Benevento',
    'BG' => 'Bergamo',
    'BI' => 'Biella',
    'BO' => 'Bologna',
    'BZ' => 'Bolzano',
    'BS' => 'Brescia',
    'BR' => 'Brindisi',
    'CA' => 'Cagliari',
    'CL' => 'Caltanissetta',
    'CB' => 'Campobasso',
    'CI' => 'Carbonia-Iglesias',
    'CE' => 'Caserta',
    'CT' => 'Catania',
    'CZ' => 'Catanzaro',
    'CH' => 'Chieti',
    'CO' => 'Como',
    'CS' => 'Cosenza',
    'CR' => 'Cremona',
    'KR' => 'Crotone',
    'CN' => 'Cuneo',
    'EN' => 'Enna',
    'FM' => 'Fermo',
    'FE' => 'Ferrara',
    'FI' => 'Firenze',
    'FG' => 'Foggia',
    'FC' => 'Forlì-Cesena',
    'FR' => 'Frosinone',
    'GE' => 'Genova',
    'GO' => 'Gorizia',
    'GR' => 'Grosseto',
    'IM' => 'Imperia',
    'IS' => 'Isernia',
    'SP' => 'La Spezia',
    'AQ' => 'L\'Aquila',
    'LT' => 'Latina',
    'LE' => 'Lecce',
    'LC' => 'Lecco',
    'LI' => 'Livorno',
    'LO' => 'Lodi',
    'LU' => 'Lucca',
    'MC' => 'Macerata',
    'MN' => 'Mantova',
    'MS' => 'Massa-Carrara',
    'MT' => 'Matera',
    'ME' => 'Messina',
    'MI' => 'Milano',
    'MO' => 'Modena',
    'MB' => 'Monza e della Brianza',
    'NA' => 'Napoli',
    'NO' => 'Novara',
    'NU' => 'Nuoro',
    'OT' => 'Olbia-Tempio',
    'OR' => 'Oristano',
    'PD' => 'Padova',
    'PA' => 'Palermo',
    'PR' => 'Parma',
    'PV' => 'Pavia',
    'PG' => 'Perugia',
    'PU' => 'Pesaro e Urbino',
    'PE' => 'Pescara',
    'PC' => 'Piacenza',
    'PI' => 'Pisa',
    'PT' => 'Pistoia',
    'PN' => 'Pordenone',
    'PZ' => 'Potenza',
    'PO' => 'Prato',
    'RG' => 'Ragusa',
    'RA' => 'Ravenna',
    'RC' => 'Reggio Calabria',
    'RE' => 'Reggio Emilia',
    'RI' => 'Rieti',
    'RN' => 'Rimini',
    'RM' => 'Roma',
    'RO' => 'Rovigo',
    'SA' => 'Salerno',
    'VS' => 'Medio Campidano',
    'SS' => 'Sassari',
    'SV' => 'Savona',
    'SI' => 'Siena',
    'SR' => 'Siracusa',
    'SO' => 'Sondrio',
    'TA' => 'Taranto',
    'TE' => 'Teramo',
    'TR' => 'Terni',
    'TO' => 'Torino',
    'OG' => 'Ogliastra',
    'TP' => 'Trapani',
    'TN' => 'Trento',
    'TV' => 'Treviso',
    'TS' => 'Trieste',
    'UD' => 'Udine',
    'VA' => 'Varese',
    'VE' => 'Venezia',
    'VB' => 'Verbano-Cusio-Ossola',
    'VC' => 'Vercelli',
    'VR' => 'Verona',
    'VV' => 'Vibo Valentia',
    'VI' => 'Vicenza',
    'VT' => 'Viterbo',
	);
  $form['supporto_istanze_content4']['supporto_istanze_provincia'] = array(
    '#type' => 'select',
    '#title' => 'Provincia',
	'#options' => $province,
    '#default_value' => variable_get('supporto_istanze_provincia', 'AG'),
  );
  $form['supporto_istanze_content4']['supporto_istanze_fax'] = array(
    '#type' => 'textfield',
    '#title' => 'Fax',
    '#default_value' => variable_get('supporto_istanze_fax', ''),
  );
  $form['supporto_istanze_content4']['supporto_istanze_telefono'] = array(
    '#type' => 'textfield',
    '#title' => 'Telefono',
    '#default_value' => variable_get('supporto_istanze_telefono', ''),
  );

  $form['#submit'][] = '_supporto_istanze_reset_fields';
  return system_settings_form($form);
}